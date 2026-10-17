# DFBHD.exe 炸药包 powerupdef 代码洞补丁分析报告

> 目标：在《三角洲特种部队1：黑鹰坠落》(DFBHD.exe, V1.5.0.5) 的 ITEMS.DEF 中给
> id 101891（Satchel Charge 炸药包，move/ai=schl、disk=EXPLOSV）添加
> `powerupdef AmmoFull`，实现"走近地上的炸药包拾取即回满弹药"，且不崩溃。
> 状态：**v2 补丁实测成功**（不崩 + 拾取回满弹药）。

---

## 1. 崩溃根因（SYSDUMP + 静态反汇编实锤）

原版加 `powerupdef` 后丢出即崩：

```
AV @ EIP=0x004AFFB8，尝试读取 0x0000002C（EAX=0）
```

崩溃点位于拾取/交互评估例程 **0x4AFF40**（调用点 0x4B05A4，参数
`[ebp+8]=obj`、`[ebp+0xC]=结果字节指针`，结果 0xFF=不可用）：

```asm
0x4AFF8F  mov  eax,[esi+0x24]        ; ITEM 记录指针
0x4AFF92  mov  ebx,[eax+0x34]        ; 标志 dword（powerupdef 标志 = bit 0x2）
0x4AFF98  je   普通路径               ; 无标志 → 正常评估
0x4AFFA7  mov  ecx,[esi+0x28]
0x4AFFAA  test ecx,ecx
0x4AFFAC  mov  eax,[esi+0x198]       ; powerup 定义记录指针
0x4AFFB2  je   0x4B02A7              ; 仅判空 obj+0x28，不判空 eax
0x4AFFB8  mov  ecx,[eax+0x2C]        ; ← EAX=0 时在此 AV
```

**根因**：`obj+0x198`（powerup 定义指针）只有走 POWERUP disk 注册链才会被填充。
炸药包的 disk_function 是 EXPLOSV、move_function 是 schl，永远不经过 POWERUP 注册，
于是 `+0x198=0`；而评估代码在标志置位后直接解引用 `[eax+0x2C]`，缺少判空——
属于该引擎"缺 NULL 检查"系列缺陷之一（JointOps 同族缺陷在 0x50FB55 读 +0x2C0）。

## 2. 引擎 powerup 注册链（capstone 静态定论）

### 2.1 分发表

- **disk_function 名表 @0x63BF78**（stride 20，`{name[16]; fn}`，9 条目）：
  GENERIC→0x46E2D0、**POWERUP→0x48C9F0**、ORGANIC→0x441DA0、PLAYER→0x441EA0、
  HELO→0x441EC0、EMPLACE→0x441F00、LANDMINE→0x4D54D0、EXPLOSV→0x4D06F0、MARKER→0x442070
- move_function 名表在其上方（stride 16，`{name[8]; fn}`），schl→0x4D1580

### 2.2 注册函数 PU_REG = 0x48C6B0（__cdecl，单 obj 参数）

- powerupdef 名取自 **ITEM 记录 +0x790**（字符串）
- 定义表：**基址 dword[0x96D1B8]、计数 dword[0x96D1B0]、步长 0xB8**
- 按名匹配调用 strcmp **0x5C3570**（返回 0 = 匹配）
- 命中后写入对象字段：
  | 字段 | 值 | 含义 |
  |---|---|---|
  | obj+0x198 | def 指针 | powerup 定义记录 |
  | obj+0x224 | 0x48B580 | 每帧 mover |
  | obj+0x190 | [def+0x20] | |
  | obj+0x194 | [def+0x24] | 拾取应用回调 |
  | obj+0x1a0 | [def+0xB4]-1（≤0 则 -1） | 可拾取次数 |
  | obj+0x18c | -1 | "未上膛"（0 才可拾取） |

### 2.3 拾取 mover = 0x48B580

- 全局门 `[0x9F2190]`；`+0x1a0==0` 返回；`+0x18c>0` 冷却递减；`+0x18c<0` 跳过
- **仅 `+0x18c==0` 时执行拾取**：调用 `[obj+0x194]`（def+0x24 回调，即回满弹药的应用
  函数 0x48B5F0 一族），随后扣减 `+0x1a0`
- 拾取后仅当 `word[obj+0x19E] != 0` 才调用 0x48C8A0（特效/字符串逻辑）

### 2.4 关键教训：PU_REG 不可对非 POWERUP 形状对象直接调用

v1 补丁在代码洞内 `call PU_REG`，实测触碰炸药包即崩：

```
AV @ EIP=0x77952D59（ntdll 内 strlen 扫描循环），读 0x0012B078
栈上返回地址 0x0048CF76 = 0x48C8A0 内 call 0x55D400 之后
```

原因：PU_REG 的尾部逻辑（EFFECT 表查找 0x518AB0 把 `[obj+0x28]` 当 0xB8 步长表
基址搜字符串 "EFFECT"@0x63CF7C，以及 0x48C8A0 把 `[obj+0x88]`、记录 +0x294/+0x2B4
当字符串处理）**假定对象是真 POWERUP 形状**。炸药包对象这些字段是垃圾数据，
扫描/strlen 直接踩未映射页。

## 3. v2 补丁设计（实测成功）

### 3.1 PE 结构：新增独立可执行节 `.joext`

| 项 | 值 |
|---|---|
| RVA / VA | 0xB72000 / 0x00F72000 |
| raw offset / size | 0x26E000 / 0x1000 |
| Characteristics | 0x60000020 (CODE\|EXECUTE\|READ) |
| 节表条目 | 7 → 8（节表后空位 0xCB8 足够） |
| SizeOfImage | → 0xB73000 |
| 文件大小 | 2547712 → **2551808** 字节 |

### 3.2 挂钩

0x4AFFA7 处 5 字节 `8B 4E 28 85 C9` → `E9 rel32` 跳入洞（长度精确匹配，
跳回点 0x4AFFB2 指令边界完好）。

### 3.3 代码洞（264 字节）：内联"最小注册"

寄存器约束：eval 后续路径存活 ebx/edx/edi/esi，**洞只能破坏 eax/ecx**。

流程：

1. `[esi+0x198] != 0`（已注册，真 powerup）→ 复刻原 3 条指令跳回 0x4AFFB2
2. `[esi+0x28] == 0` → 跳 0x4B02A7（原生"结果 0xFF 不可用"返回路径）
3. 否则 `sub esp,8` 暂存 name（记录+0x790）与索引 i，循环：
   `def = [0x96D1B8] + i*0xB8`，`push def / push name / call 0x5C3570`，
   匹配即 FOUND；`i >= [0x96D1B0]` 未命中 → 保持 +0x198=0 走原生跳过
4. FOUND 只写安全字段：`+0x224=0x48B580`、`+0x198=def`、`+0x190=[def+0x20]`、
   `+0x194=[def+0x24]`、`+0x1a0=([def+0xB4]>0 ? [def+0xB4]-1 : -1)`、
   并清零 `+0x19C/+0x19D/+0x19E(word)/+0x230` —— **其中 +0x19E=0 使 mover
   永远不会调用危险的 0x48C8A0**
5. 最后写 `+0x18C=0`（上膛），复刻现场跳回 0x4AFFB2

### 3.4 验证方法

- 洞机器码用 capstone 逐条反汇编核对：全部 jcc/jmp/call 目标、esp 平衡
  （`sub esp,8` 与两条出口 `add esp,8` 配对）均正确
- 编码教训：imm8/disp8 形式对 0xB8 会符号扩展成 -72/-0x4C，必须用
  imm32（`69 C0 B8 00 00 00`）/ disp32（`8B 81 B4 00 00 00`）
- 游戏内实测：触碰炸药包不崩 → 走近拾取 → 弹药回满 ✓

## 4. 交付物

| 文件 | MD5 | 说明 |
|---|---|---|
| `DFBHD_satchel_powerup_v2.exe` | `EDEC0581F37F4BE5BC195CAC69DD98AD` | 2551808 字节，基于原版 |
| 原版 `DFBHD.exe` | `D6F51AD03CA62F040586B8B5E3CA8181` | 2547712 字节 |

使用方法：把 v2 exe 复制进游戏目录替换 DFBHD.exe，保留修改后的 ITEMS.DEF
（id 101891 带 `powerupdef AmmoFull`）即可。

注意：v2 基于**原版** exe，不含 medpack 自疗/全兵种补丁；如需三合一可另行叠加。
