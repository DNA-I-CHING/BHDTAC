# JointOps medpack 自他排除分析与补丁报告

> 目标：使 medpack（医疗包）弹药也能给投掷者自己回血（原版只治疗队友）。
> 分析对象：`jointops.exe`（32 位 PE，ImageBase 0x400000，4612096 字节，原版 MD5 `CB19DCAAFEFF25D5518A49EC9AFAD420`）。
> 分析方式：本地 capstone 静态反汇编 + 字节级取证（file_offset = VA − 0x400000 对全部节直接成立）。
> 补丁方式：2 字节 NOP，不新增代码、不改文件大小。

---

## 1. medpack 机制背景

medpack 在 `ammo.def` 中是一条带 `instantkillzone` 标志（bit 0x400）且 `kztype = rounds_kz_Medic`（枚举值 3）的"瞬时杀伤区"弹药：

- ammo 标志 dword 位于 AMMO 记录 +0x00；`instantkillzone = 0x400`。
- `kztype` 位于 AMMO 记录 +0x2C（word）；kztype 枚举表 @0x8133E0：null=0 / Standard=2 / **Medic=3** / RadiusBlast=4 / C4=5 / Bullets=6 / Slash=7。
- 杀伤区参数：kz_pieslice=+0x30、kz_minradius=+0x34、kz_maxradius=+0x38（medpack 半径 2）。

它与 powerup 拾取链完全无关，回血效果在投射物命中瞬间通过杀伤区结算完成。

## 2. 完整调用链（静态实锤）

```
ammo 命中处理函数
  0x4ec1ed  test dword[ammo记录], 0x400      ; instantkillzone 标志
  0x4ec20e  call 0x4e83c0                     ; 入队（8 参数）
        ↓
0x4e83c0  瞬时杀伤区事件队列 pusher
  队列：0x40 项 × 0x34 字节，计数 dword @0xB7C680，基址 @0xB7C688
  条目字段：+0x00..0x08 落点坐标 / +0x18 = kztype / +0x1C = AMMO 记录指针
            / +0x20 = 投掷者玩家对象指针 / +0x28 = word
        ↓
0x4ead80  队列处理器（每帧消费）
  0x4eadb7  mov ecx, [esi+0x18] ; sub ecx,1 ; 查跳转表 0x4EB8CC（按 kztype-1）
  跳转表：kztype 1→0x4eae0c / 2→0x4eadcd / 3→0x4eaddd / 4→0x4eae3c / 5..7→0x4eadcd
  Medic(kztype=3) → case 0x4eaddd → handler 指针 [esp+0x24] = 0x4E6790
        ↓
0x4eaf00  玩家遍历循环（玩家表 0xA892E0/0xA892E4/0xA892E8）
  半径/角度(pieslice)/死亡标志/团队检查逐玩家过滤
  0x4eb078  cmp kztype,3 / je → Medic 在循环层放行 owner（不排除自己）
  0x4eb312  call dword[esp+0x34]               ; 调用 handler(edi=玩家, esi=队列条目)
        ↓
0x4e6790  Medic 效果 handler（仅 kztype=3 使用）
  0x4e67a3  mov eax, [edi+0x20]                ; 队列条目 +0x20 = 投掷者玩家对象
  0x4e67a6  cmp esi, eax                       ; 当前玩家 == 投掷者？
  0x4e67a8  je  0x4e680d                       ; ★ 自他排除：相等则跳过治疗
  ...
  0x4e67b7  cmp 队伍(+0x162)                    ; 队友校验
  0x4e67e3  call 0x43b8a0 / 比较HP / call 0x50de30(投掷者,玩家)   ; 治疗应用
  0x4e67d6  call 0x517cd0(投掷者,玩家)                            ; 倒地拉起
```

**结论**：自他排除不是写在遍历循环里（循环层对 Medic 反而放行 owner），而是写死在 Medic handler `0x4E6790` 开头的一条 `cmp/je`。

## 3. 补丁

| 项目 | 值 |
|---|---|
| 文件偏移 | `0xE67A8`（VA 0x4E67A8） |
| 原字节 | `74 63`（`je 0x4e680d`） |
| 补丁字节 | `90 90`（NOP ×2） |
| 改动量 | 全文件仅 2 字节 |
| 文件大小 | 4612096（不变） |
| 补丁后 MD5 | `39C22F7566F2EE5CC1DC3AECED9926C3` |
| 原版 MD5 | `CB19DCAAFEFF25D5518A49EC9AFAD420` |

NOP 后执行流从 `0x4e67a8` 落入 `0x4e67aa`（`mov ecx,2; test byte[eax+0x24],cl`），继续走队友校验（owner 与自己比较必然相等）、HP 判断与治疗应用 `0x50de30`，逻辑完整。

**影响范围**：`0x4E6790` 仅被 kztype=Medic 分发使用；satchel/C4/Standard 等杀伤区走 `0x4E6820` handler，完全不受影响。

## 4. 关键地址速查表

| 地址 | 含义 |
|---|---|
| 0x4EC1ED | 命中处理中 `test [ammo],0x400`（instantkillzone 判定） |
| 0x4EC20E | call 入队 |
| 0x4E83C0 | 瞬时杀伤区事件入队函数（队列 0xB7C688，计数 0xB7C680） |
| 0x4EAD80 | 队列处理器（按 kztype 分发） |
| 0x4EB8CC | kztype→case 跳转表（索引 = kztype−1） |
| 0x4EAF00 | 玩家遍历循环（半径/角度/团队过滤） |
| 0x4EB312 | handler 调用点 `call [esp+0x34]` |
| **0x4E6790** | **Medic handler（自他排除所在）** |
| **0x4E67A8** | **补丁点 `74 63`→`90 90`** |
| 0x50DE30 | 治疗应用（投掷者, 玩家） |
| 0x517CD0 | 倒地拉起（投掷者, 玩家） |
| 0x4E6820 | 伤害类杀伤区 handler（不受影响） |
| 0x8133E0 | kztype 枚举表 |
| 0x813500 | ammo flag 名表 |
