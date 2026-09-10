# 月湖夜钓（Moonlake Fishing）· C 语言版

基于 C 语言的游戏开发实践 —— 命令行文字版钓鱼游戏。

## 项目简介

本程序用纯 C 语言实现《月湖夜钓》的核心玩法：三关夜钓、鱼种随机、连击计分、结局评级，并附带鱼种图鉴、菜谱查看、最高分存档等功能。

## 模块划分（每个板块对应一个 C 文件）

| 文件 | 模块 | 知识点 |
|------|------|--------|
| `main.c` | 主程序（菜单、关卡流程、交互） | 函数、流程控制、循环 |
| `fish.h` / `fish.c` | 鱼种数据模块 | 结构体、枚举、结构体数组、指针 |
| `hook.h` / `hook.c` | 鱼钩状态机模块 | enum + switch 状态机 |
| `combat.h` / `combat.c` | 连击与计分模块 | 函数、条件分支 |
| `scale.h` / `scale.c` | 刮鳞评级模块 | 枚举、switch 多分支 |
| `cook.h` / `cook.c` | 菜谱烹饪模块 | 结构体、函数调用 |
| `save.h` / `save.c` | 存档模块 | 文件操作（fopen/fscanf/fprintf） |

## 编译方法

### Visual Studio（推荐）

1. 新建「控制台应用」项目（语言选 C，或把源文件后缀改为 `.c`）。
2. 把本目录所有 `.c` / `.h` 文件加入项目。
3. 若编译报中文编码错误（如「常量中有换行符」），请在项目属性 → C/C++ → 命令行 中加 `/utf-8`，或将源文件另存为「UTF-8 带 BOM」。
4. 生成并运行。

### 命令行（MinGW / gcc）

```bash
gcc main.c fish.c hook.c combat.c scale.c cook.c save.c -o fish_game
./fish_game
```

### 命令行（MSVC cl）

```bash
cl /utf-8 main.c fish.c hook.c combat.c scale.c cook.c save.c /Fe:fish_game.exe
```

## 玩法说明

- 主菜单选择 1 开始夜钓，共 3 关。
- 每关有若干次抛竿机会，输入 `c` 抛竿，等待鱼上钩。
- 鱼咬钩后输入 `r` 收竿（只有一次机会，慢了鱼会脱钩）。
- 连续成功会积累连击，得分倍率最高 ×5。
- 三关结束按总分结算 S/A/B/C 结局，最高分自动存档。
