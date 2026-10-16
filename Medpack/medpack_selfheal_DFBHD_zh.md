# Delta Force: Black Hawk Down（DFBHD.exe）medpack 自疗与全兵种治疗分析与补丁报告

> 目标一：使 medpack（医疗包）弹药也能给投掷者自己回血（原版只治疗队友）。
> 目标二（--allclasses / v3 补丁）：原版只有医疗兵（medic，兵种 id 6/0xA）投掷的 medpack 才能治疗，cqb/sniper/gunner 及单人模式无效；补丁后任何兵种、任何模式投掷均可治疗。
> 分析对象：`DFBHD.exe`（黑鹰坠落本体，与 JointOps 同引擎；32 位 PE，ImageBase 0x400000，2547712 字节，原版 MD5 `D6F51AD03CA62F040586B8B5E3CA8181`）。
> 分析方式：本地 capstone 静态反汇编 + 字节级取证（file_offset = VA − 0x400000 对全部节直接成立）。
> 补丁方式：全部为 2 字节原地修改（NOP 或 je→jmp），不新增代码、不改文件大小。

---

## 1. medpack 机制背景

与 JointOps 相同，medpack 是一条带 `instantkillzone` 标志且 `kztype = rounds_kz_Medic`（枚举值 3）的"瞬时杀伤区"弹药，回血在投射物命中瞬间通过杀伤区结算完成，与 powerup 拾取链无关。

引擎字符串在本体中均可定位，确认同引擎同机制：

| 字符串 | VA |
|---|---|
| `rounds_kz_Medic` | 0x61FD48 |
| `instantkillzone` | 0x61FBC0 |
| `ownerimmune` | 0x61FBB4 |

## 2. 完整调用链（静态实锤）

```
瞬时杀伤区队列处理器
  0x493670  队列基址 0x9D71C8，计数 dword [0x96ED50]
  条目字段：+0x18 = kztype / +0x1C = AMMO 记录指针 / +0x20 = 投掷者玩家对象
  0x4936ad  mov ecx, [esi+0x18]              ; 直接取 kztype
  0x4936b9  jmp dword [ecx*4 + 0x4940EC]     ; 跳转表（索引 = kztype 本身）
  跳转表：0→0x4936F4 / 1→0x4936FC / 2→0x4936C0 / 3→0x4936C8
          / 4→0x49372C / 5,6,7→0x4936C0
  Medic(kztype=3) → case 0x4936C8
    0x4936d6  call 0x418ec0([投掷者+0x244]兵种字节, 8) ; 兵种能力位查表（medic 才有 bit8）
    0x4936e0  je  0x4936f4                          ; ★ 兵种门1：非 medic 不装载 handler
    0x4936eb  mov dword [ebp-0x14], 0x492EE0        ; 装载 Medic handler
        ↓
  逐玩家遍历后调用 handler(esi=玩家, edi=队列条目)
        ↓
0x492EE0  Medic 效果 handler（仅 kztype=3 装载）
  0x492ee7  mov eax, [esi+0x24]              ; 玩家的物品记录
  0x492eea  cmp dword [eax+0x38], 3          ; itemtype == 3
  0x492ef4  mov eax, [edi+0x20]              ; 队列条目 +0x20 = 投掷者玩家对象
  0x492ef7  cmp esi, eax                     ; 当前玩家 == 投掷者？
  0x492ef9  je  0x492f63                     ; ★ 自他排除：相等则跳过治疗
  0x492f0a  cmp 队伍字段(+0xF6)              ; 队友校验
  0x492f3a  call 0x441b90 / 比较HP(+0xE2) / call 0x4AF0D0(玩家, 投掷者)   ; 治疗应用
  0x492f2d  call 0x4AEE40(玩家, 投掷者)                                    ; 倒地拉起
```

**结论**：与 JointOps 完全同构——自他排除写死在 Medic handler `0x492EE0` 开头的一条 `cmp/je`，而非遍历循环。定位方法：JointOps 门控的精确字节签名 `8b 47 20 3b f0 74` 在本文件全扫描**唯一命中 0x492EF4**，反汇编上下文逐结构验证吻合。

## 3. 自疗补丁（单门）

| 项目 | 值 |
|---|---|
| 文件偏移 | `0x92EF9`（VA 0x492EF9） |
| 原字节 | `74 68`（`je 0x492f63`） |
| 补丁字节 | `90 90`（NOP ×2） |
| 改动量 | 全文件仅 2 字节 |
| 文件大小 | 2547712（不变） |
| 补丁后 MD5 | `AC1CC9518F1651FF1BAF31044D497CBB` |
| 原版 MD5 | `D6F51AD03CA62F040586B8B5E3CA8181` |

NOP 后执行流从 `0x492ef9` 落入 `0x492efb`（读取投掷者标志字节），继续走队友校验（投掷者与自己比较必然相等）、HP 判断与治疗应用 `0x4AF0D0`，逻辑完整。

**影响范围**：`0x492EE0` 仅在跳转表 kztype=3（Medic）分支被装载；Standard/RadiusBlast/C4/Bullets/Slash 等杀伤区走 `0x492F70` 伤害 handler 或其他 case，完全不受影响。

## 4. 兵种限制分析（三道兵种门，静态实锤）

原版只有 medic 兵种投掷的 medpack 生效，限制分布在**三道独立门控**上，只 NOP 分发门（门1）依然无效——治疗应用与复活函数内部还有第二、三道门：

### 门 1：分发门（handler 装载条件）— 0x4936E0

```
0x4936c8  mov eax, [esi+0x20]                  ; esi=队列条目, +0x20=投掷者玩家对象
0x4936cd  mov cl, byte [eax+0x244]             ; 兵种 id 字节
0x4936d3  push 8                               ; 能力位 = 8（medic 治疗能力）
0x4936d5  push ecx
0x4936d6  call 0x418ec0                        ; 兵种能力位查表
0x4936de  test eax, eax
0x4936e0  je  0x4936f4                         ; ★ 返回 0 → handler 置空，不装载
0x4936eb  mov dword [ebp-0x14], 0x492EE0       ; 装载 Medic handler
```

- `0x418ec0(id, bit)` 查兵种能力表：表基址 0x715b80、条目步长 0x84、掩码字段 record+0x28；只有 medic 的条目带 bit 8。
- **单人模式失效根因**：能力表指针 `[0x715b48]` 在单人模式下为 0，函数直接返回 0 → 分发门必然失败 → Medic handler 永不装载。

### 门 2：治疗应用门 — 0x4AF0D0 内部（补丁点 0x4AF13D）

handler 放行后，治疗应用函数 `0x4AF0D0(玩家, 投掷者)` 还要校验**投掷者兵种**：

```
遍历玩家记录表 [0x9ED600]（步长 0xAF33C，记录+0x18=玩家对象指针，+0x68c4=槽有效）
找到投掷者记录 ebx 后：
0x4af134  mov eax, [ebx+0x68A0]                ; 投掷者兵种 id（记录字段）
0x4af13a  cmp eax, 6
0x4af13d  je  0x4af148                         ; medic(6) → 放行
0x4af13f  cmp eax, 0xA
0x4af142  jne 0x4af20c                         ; ★ 兵种非 6/0xA → 返回，不治疗
```

补丁：`0x4AF13D` 处 `74`（je）→ `EB`（jmp），任何兵种都走放行分支 `0x4af148`。

### 门 3：复活门 — 0x4AEE40 内部（补丁点 0x4AEEF3）

倒地拉起函数 `0x4AEE40` 有同样结构的兵种校验（直接读投掷者对象字段）：

```
0x4aeeea  mov ecx, [esi+0x244]                 ; 投掷者兵种 id 字节
0x4aeef0  cmp ecx, 6
0x4aeef3  je  0x4aeefe                         ; medic(6) → 放行
0x4aeef5  cmp ecx, 0xA
0x4aeef8  jne 0x4af0bf                         ; ★ 兵种非 6/0xA → 返回，不拉起
```

补丁同为 `0x4AEEF3` 处 `74`→`EB`。

> 附注：`0x418ec0` 在全文件共 6 个调用点，其余 3 个（0x4aa034 / 0x507a25 / 0x50bada）均为弹药箱拾取限制，与 killzone 治疗无关，不受本补丁影响。

## 5. 全兵种补丁（v3，实测有效）

在自疗补丁（第 3 节）基础上叠加三道兵种门，共 4 处 2 字节修改（je→jmp 各只改 1 个物理字节，实际 diff 6 字节）：

| # | 文件偏移 | VA | 原字节 | 补丁字节 | 作用 |
|---|---|---|---|---|---|
| 1 | `0x92EF9` | 0x492EF9 | `74 68` | `90 90` | 自疗：NOP 投掷者==自己跳过治疗 |
| 2 | `0x936E0` | 0x4936E0 | `74 12` | `90 90` | 兵种门1：分发无条件装载 handler |
| 3 | `0xAF13D` | 0x4AF13D | `74 09` | `EB 09` | 兵种门2：治疗应用放行所有兵种 |
| 4 | `0xAEEF3` | 0x4AEEF3 | `74 09` | `EB 09` | 兵种门3：复活放行所有兵种 |

| 项目 | 值 |
|---|---|
| 补丁文件 | `DFBHD_medpack_v3.exe` |
| 改动量 | 6 字节 |
| 文件大小 | 2547712（不变） |
| 补丁后 MD5 | `1E3DDF254828A04F6610BD3C4A57ADBA` |
| 原版 MD5 | `D6F51AD03CA62F040586B8B5E3CA8181` |

**效果**：任何兵种（cqb/sniper/gunner/engineer/medic）、任何模式（含单人）投掷 medpack 均可治疗自己与队友；伤害类杀伤区（satchel/C4 等）不受影响。

**生成方式**：`python patch_medpack_selfheal.py DFBHD.exe DFBHD_medpack_v3.exe --allclasses`（脚本对 JointOps 自动只打自疗门；幂等，可在 selfheal 版上直接叠加 `--allclasses`）。

## 6. 关键地址速查表

| 地址 | 含义 |
|---|---|
| 0x493670 | 瞬时杀伤区队列处理器（按 kztype 分发） |
| 0x9D71C8 | 队列条目基址（计数 dword [0x96ED50]） |
| 0x4940EC | kztype→case 跳转表（索引 = kztype 本身） |
| 0x4936C8 | Medic case（条件装载 handler） |
| 0x418EC0 | 兵种能力位查表（表基址 0x715B80 步长 0x84，表指针 [0x715B48] 单人模式为 0） |
| **0x492EE0** | **Medic handler（自他排除所在）** |
| **0x492EF9** | **补丁点1 自疗 `74 68`→`90 90`** |
| **0x4936E0** | **补丁点2 分发兵种门 `74 12`→`90 90`** |
| 0x4AF0D0 | 治疗应用（玩家, 投掷者），内含兵种门 |
| **0x4AF13D** | **补丁点3 治疗应用兵种门 `74`→`EB`** |
| 0x4AEE40 | 倒地拉起（玩家, 投掷者），内含兵种门 |
| **0x4AEEF3** | **补丁点4 复活兵种门 `74`→`EB`** |
| 0x9ED600 | 玩家记录表基址（步长 0xAF33C，记录+0x68A0=兵种 id） |
| 0x441B90 | 玩家最大 HP 查询 |
| 0x492F70 | 伤害类杀伤区 handler（不受影响） |
| 0x9F2190 | 效果启用全局开关（须非 0） |
| 0x61FD48 | `rounds_kz_Medic` 字符串 |

> 与 JointOps 版本的字段偏移差异：物品记录指针 玩家+0x24（JO 为 +0x20）、itemtype 记录+0x38（JO 为 +0x5c）、队伍字段 +0xF6（JO 为 +0x162）、HP 字段 +0xE2（JO 为 +0x11e）、标志字节 +0x20 bit4（JO 为 +0x24 bit2）。跳转表索引方式亦不同：DFBHD 直接用 kztype，JO 用 kztype−1。
