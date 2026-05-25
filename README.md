A high-performance poker engine designed for real-time gameplay and simulation.
# Texas Hold'em Poker Engine

[![GitHub stars](https://img.shields.io/github/stars/deepseek7878/texas-holdem-engine?style=for-the-badge)](https://github.com/deepseek7878/texas-holdem-engine)
[![GitHub forks](https://img.shields.io/github/forks/deepseek7878/texas-holdem-engine?style=for-the-badge)](https://github.com/deepseek7878/texas-holdem-engine)
[![GitHub issues](https://img.shields.io/github/issues/deepseek7878/texas-holdem-engine?style=for-the-badge)](https://github.com/deepseek7878/texas-holdem-engine/issues)
[![GitHub license](https://img.shields.io/github/license/deepseek7878/texas-holdem-engine?style=for-the-badge)](https://github.com/deepseek7878/texas-holdem-engine/blob/main/LICENSE)
[![Release](https://img.shields.io/github/v/release/deepseek7878/texas-holdem-engine?style=for-the-badge)](https://github.com/deepseek7878/texas-holdem-engine/releases)

**Professional Texas Hold'em poker engine / 德州源码 / 德州俱乐部源码/德州二开/wpk/专业德州扑克游戏引擎 / 專業德州撲克遊戲引擎**  

**真实运营数年 · 支持线下验证 ·ALLIN德州扑克源码 ·八个德州玩法，远超市场主流德州玩法**


**简体中文 · 繁體中文 · English· 韩文· 马来文· 日文· 泰文· 印尼语·越南文**

Complete Texas Hold'em rules implementation with betting, hand evaluation, table flow, and extensible architecture / 完整德州扑克规则实现，包含下注、牌型判断、牌桌流程，可扩展架构 / 完整德州撲克規則實作，包含下注、牌型判斷、牌桌流程，可擴充架構.

## 🎯 核心功能 / Key Features / 核心功能

| 模块 / Module / 模組 | 功能 / Features / 功能 |
|---|---|
| 🎴 **完整规则** | Pre-flop, flop, turn, river全流程 / 全牌局流程 / 全牌局流程 |
| 💰 **下注系统** | Raise, call, fold, all-in完整支持 / 完整下注系统 / 完整下注系統 |
| 🃏 **牌型判断** | Royal flush到高牌15种牌型 / 15种牌型精确判断 / 15種牌型精準判斷 |
| 🪑 **牌桌管理** | 2-10人桌，多桌支持 / 多桌管理 / 多桌管理 |
| 📊 **胜率计算** | 实时胜率Equity计算 / 实时胜率計算 / 即時勝率計算 |
| 🔌 **API接口** | 易于集成到Web/App / 易於整合 / 易於整合 |

## 🚀 三步启动 / 3-Step Quick Start / 三步啟動


# 1. 下载源码
git clone https://github.com/deepseek7878/texas-holdem-engine.git
cd texas-holdem-engine

# 2. 安装依赖
npm install   # Node.js
# 或
pip install -r requirements.txt  # Python

# 3. 运行示例
npm run demo  # 运行Demo
# 或
python demo.py


**访问 `http://localhost:3000` 体验完整牌局！ / Experience full gameplay! / 體驗完整牌局！联系Telegram：@fox_lovemyself**

## 📱 💰 获取源码 | Contact


📱 Telegram：@fox_lovemyself


📧 Email：lihongbo9414@gmail.com

## 📱 实时演示 / Live Demo / 即時示範

![FCECCB0C93E7DDC2C04274DEE551FB24](https://github.com/user-attachments/assets/9885072d-c75d-4fd8-84e4-e8a65250e10d)
![牌桌1-9人](https://github.com/user-attachments/assets/adad8858-9ed3-4554-a00a-89f900636408)
---

## 🎮 完整游戏流程 / Full Game Flow / 完整遊戲流程
1：玩家加入牌桌 (2-10人)
2:发底牌 (2张 hole cards)

3:Pre-flop 下注轮

4:Flop 发3张公共牌

5:Turn 发第4张公共牌

6:River 发第5张公共牌

7:摊牌 → 牌型比较 → 底池分配

8:下一局开始


## 🏗️ 核心架构 / Core Architecture / 核心架構
texas-holdem-engine/
├── core/
│ ├── deck.js # 52张扑克牌管理
│ ├── handEvaluator.js # 牌型判断引擎
│ ├── betting.js # 下注系统
│ └── table.js # 牌桌管理
├── players/ # 玩家对象
├── game/ # 游戏流程控制
└── api/ # 外部接口

## 💎 技术亮点 / Technical Highlights / 技術亮點
✅ 精确牌型排序 (Royal Flush > Straight Flush...)
✅ 底池分配算法 (Side pots, all-in处理)
✅ 胜率Equity实时计算
✅ 事件驱动架构
✅ TypeScript类型安全 (可选)
✅ 单元测试覆盖 >85%

## 🎯 集成示例 / Integration Examples / 整合範例

### Web集成
```javascript
import { Table, Player } from 'texas-holdem-engine';

const table = new Table(9);
const player1 = new Player('Alice', 1000);
table.join(player1);
table.startNewHand();
```

### Python集成
```python
from engine import Table, Player
table = Table(6)
player = Player("Bob", 500)
table.add_player(player)
table.deal_hands()
```
## 🧠 Core Engine Capabilities | 核心引擎能力

- Poker hand evaluation system  
- Game state transition engine  
- Action validation logic  
- Round & betting flow control
## 🔌 API Example

```js
engine.createGame()
engine.joinPlayer()
engine.startRound()
engine.processAction(player, action)
## 🎯 Simulation Support

- Multi-round simulation  
- Strategy testing environment  
- AI integration ready

## 📊 性能指标 / Performance / 效能指標

| 测试项目 | 性能 | 备注 |
|---|---|---|
| 牌型判断 | <1ms | 15种牌型 |
| 1000手模拟 | 45ms | 9人桌 |
| 胜率计算 | 12ms | Monte Carlo |
| 内存占用 | 25MB | 空闲状态 |

---

## 🎯 适用场景 / Use Cases / 適用場景

- 🎰 **在线扑克平台** - 核心游戏引擎
- 📱 **扑克App** - 移动端游戏
- 🤖 **AI训练** - 强化学习环境
- 🎮 **娱乐小程序** - 社交扑克房
- 📚 **教学演示** - 扑克规则学习

## 🛠️ 版本发布 / Releases / 版本發佈

### ⭐ v1.0.0 (最新)
✅ 完整德州扑克规则  
✅ 15种牌型精确判断  
✅ 多桌并发支持  
✅ API文档完整  
✅ 单元测试覆盖  

**[下载最新版](https://github.com/deepseek7878/texas-holdem-engine/releases/latest)**

## ❓ 常见问题 / FAQ / 常見問題

**Q: 支持多人同时游戏吗？**  
**A:** 支持多桌并发，单实例100+桌无压力

**Q: 牌型判断准确吗？**  
**A:** 覆盖15种牌型，经过大量测试验证

**Q: 可以商用吗？**  
**A:** MIT License，完全商用友好

**Q: 支持AI玩家吗？**  
**A:** 提供完整Player接口，易于集成AI

## 🤝 贡献指南 / Contributing / 貢獻指南
Fork → 创建特性分支

开发 → 测试 → 提交PR

欢迎贡献: 新功能、性能优化、Bug修复

## 📄 开源许可 / License / 授權

MIT License - 商业友好
个人使用 | 商业部署 | 二次开发 | AI训练
Copyright (c) 2026 deepseek7878

---

**⭐ Star支持专业扑克引擎开源！ / Star to support professional poker engine! / Star支持專業撲克引擎開源！**


