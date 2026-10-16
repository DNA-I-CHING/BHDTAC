# Delta Force: Black Hawk Down（DFBHD.exe）medpack 自他排除分析与补丁报告

> 目标：使 medpack（医疗包）弹药也能给投掷者自己回血（原版只治疗队友）。
> 分析对象：`DFBHD.exe`（黑鹰坠落本体，与 JointOps 同引擎；32 位 PE，ImageBase 0x400000，2547712 字节，原版 MD5 `D6F51AD03CA62F040586B8B5E3CA8181`）。
> 分析方式：本地 capstone 静态反汇编 + 字节级取证（file_offset = VA − 0x400000 对全部节直接成立）。
> 补丁方式：2 字节 NOP，不新增代码、不改文件大小。

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
    0x4936d6  call 0x418ec0(8, [投掷者+0x244])   ; 投掷者有效性检查
    0x4936eb  mov dword [ebp-0x14], 0x492EE0     ; ★ 装载 Medic handler
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

## 3. 补丁

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

## 4. 关键地址速查表

| 地址 | 含义 |
|---|---|
| 0x493670 | 瞬时杀伤区队列处理器（按 kztype 分发） |
| 0x9D71C8 | 队列条目基址（计数 dword [0x96ED50]） |
| 0x4940EC | kztype→case 跳转表（索引 = kztype 本身） |
| 0x4936C8 | Medic case（条件装载 handler） |
| **0x492EE0** | **Medic handler（自他排除所在）** |
| **0x492EF9** | **补丁点 `74 68`→`90 90`** |
| 0x4AF0D0 | 治疗应用（玩家, 投掷者） |
| 0x4AEE40 | 倒地拉起（玩家, 投掷者） |
| 0x441B90 | 玩家最大 HP 查询 |
| 0x492F70 | 伤害类杀伤区 handler（不受影响） |
| 0x9F2190 | 效果启用全局开关（须非 0） |
| 0x61FD48 | `rounds_kz_Medic` 字符串 |

> 与 JointOps 版本的字段偏移差异：物品记录指针 玩家+0x24（JO 为 +0x20）、itemtype 记录+0x38（JO 为 +0x5c）、队伍字段 +0xF6（JO 为 +0x162）、HP 字段 +0xE2（JO 为 +0x11e）、标志字节 +0x20 bit4（JO 为 +0x24 bit2）。跳转表索引方式亦不同：DFBHD 直接用 kztype，JO 用 kztype−1。
