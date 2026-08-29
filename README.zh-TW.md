# Texas Hold'em Poker Engine — 德州撲克遊戲引擎原始碼

[English](README.en.md) | [繁體中文](README.zh-TW.md) | [GitHub Pages](https://deepseek7878.github.io/texas-holdem-engine/)

Texas Hold'em Poker Engine 是一个高性能德州撲克核心遊戲引擎原始碼專案，適合用於德州私局、俱樂部、大厅局、联盟、锦标赛、百人德州、AI 训练环境和商业扑克游戏平台的技术参考。

專案覆盖德州撲克完整牌局流程，包括发牌、下注、跟注、加注、棄牌、All-in、邊池、牌型判斷、牌桌狀態、玩家狀態、勝率計算、事件推送和多人桌管理等核心模块。

> 合规说明：请在合法地区、合法业务范围内使用。本專案適合作为游戏开发、规则引擎、模拟训练、教学演示和商业系统技术参考。

## 核心关键词

- 德州撲克原始碼
- 德州原始碼
- 德州撲克游戏引擎
- Texas Hold'em Poker Engine
- Poker Engine Source Code
- 德州俱樂部原始碼
- 德州賽事系统
- 德州撲克 App 原始碼
- 多人扑克游戏原始碼
- 勝率計算 Equity Calculator
- 扑克牌型判斷 Hand Evaluator

## 核心功能

| 模块 | 功能 |
|---|---|
| 完整规则流程 | Pre-flop、Flop、Turn、River、Showdown |
| 下注系统 | Check、Bet、Call、Raise、Fold、All-in |
| 牌型判斷 | 皇家同花顺、同花顺、四条、葫芦、同花、顺子、三条、两对、一对、高牌 |
| 邊池算法 | 支持多人 All-in、主池、邊池、分池 |
| 牌桌管理 | 支持 2-10 人桌、多桌并发、玩家狀態管理 |
| 勝率計算 | Monte Carlo 模拟、实时 Equity 计算 |
| 賽事擴充 | SNG、MTT、盲注升级、报名、淘汰、排名 |
| 俱樂部擴充 | 私局、房间、俱樂部、联盟、代理层级 |
| AI 训练 | 可用於强化学习、策略测试、机器人对局模拟 |
| API 集成 | 適合接入 Web、App、後台和运营系统 |

## 适用场景

- 德州撲克完整解决方案
- 德州私局/俱樂部系统
- 德州撲克大厅局平台
- 德州撲克賽事系统
- 扑克 App / H5 / 小程序
- AI Poker Bot 训练环境
- 扑克规则教学与模拟器
- 扑克勝率計算工具
- 海外 Texas Hold'em 游戏平台

## 推荐專案结构

```text
core/                  # 德州撲克核心规则与狀態机
server/                # 游戏服务器与房间服务
api/                   # 对外 API 接口
client-example/        # 客户端接入示例
admin/                 # 运营後台
database/              # 数据库结构与迁移
config.example/        # 脱敏配置示例
scripts/               # 构建、部署、测试脚本
docs/                  # GitHub Pages 产品与技术文档
tests/                 # 自动化测试和牌型验证
.github/workflows/     # CI 与 Pages 發布工作流
```

## 技术亮点

- 高性能 C++/TARS 服务结构，適合实时游戏场景
- 完整德州撲克狀態机，便于维护和擴充
- 支持多人桌、邊池、All-in、牌型比较等复杂逻辑
- 適合擴充为俱樂部、联盟、锦标赛和 AI 训练平台
- README、Pages、sitemap、robots 多维度提升 GitHub/Google/Bing 可发现性

## GitHub Pages 發布

上傳 `docs/` 后，推荐这样启用 Pages：

```text
Settings → Pages → Deploy from a branch
Branch: main
Folder: /docs
Save
```

發布后访问：

```text
https://deepseek7878.github.io/texas-holdem-engine/
```

Sitemap：

```text
https://deepseek7878.github.io/texas-holdem-engine/sitemap.xml
```

## Contact

请在 GitHub 仓库页面补充 Telegram、Email、官网或演示地址，便于搜索用户聯絡。
