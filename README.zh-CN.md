> [!IMPORTANT]
> **这是一个非官方分支（fork）。** 你看到的是 [**coex177**](https://github.com/coex177) 的个人分支，而非官方项目。它跟随上游，并加入了一些修复和易用性改进（见[本分支的不同之处](#本分支的不同之处)）。它与原作者无关，未获得其支持或背书。
>
> - **原始项目：** Mateus Cruz 的 [BATorrent-app/BATorrent](https://github.com/BATorrent-app/BATorrent)。官方、跨平台、已签名的构建（Microsoft Store / Homebrew / AppImage）请用它。
> - **本分支的构建：** [coex177/BATorrent 发布页](https://github.com/coex177/BATorrent/releases)，目前是 **仅 Windows 的 alpha 版**（`v4.1.0a`）。

<p align="center">
  <a href="README.md">English</a> | <a href="README.pt-BR.md">Português</a> | <b>中文</b> | <a href="README.ja.md">日本語</a> | <a href="README.ru.md">Русский</a> | <a href="README.es.md">Español</a> | <a href="README.de.md">Deutsch</a> | <a href="README.ua.md">Українська</a>
</p>

<p align="center">
  <img src="src/images/logo.svg" alt="BATorrent" width="140">
</p>

<h1 align="center">BATorrent</h1>

<p align="center">
  <i>有颜值的 BitTorrent 客户端 — 电影封面、六款主题、零广告。</i>
</p>

<p align="center">
  <a href="https://github.com/coex177/BATorrent/releases"><img alt="Fork release" src="https://img.shields.io/github/v/release/coex177/BATorrent?include_prereleases&style=flat-square&color=dc2626&label=fork%20release"></a>
  <a href="https://github.com/coex177/BATorrent/releases"><img alt="Downloads" src="https://img.shields.io/github/downloads/coex177/BATorrent/total?style=flat-square&color=dc2626"></a>
  <a href="LICENSE"><img alt="License" src="https://img.shields.io/github/license/coex177/BATorrent?style=flat-square&color=dc2626"></a>
  <img alt="Fork build" src="https://img.shields.io/badge/fork%20build-Windows%20x86__64%20·%20alpha-dc2626?style=flat-square">
</p>

<img src="https://capsule-render.vercel.app/api?type=rect&color=dc2626&height=3&width=100%25" width="100%"/>

<p align="center">
  <img src="src/images/with_startup.gif" alt="BATorrent — 打开即用，封面自动加载" width="860">
</p>

大多数 BT 客户端长得像报税表。这一个把你的下载呈现为 **一墙电影、剧集和游戏封面** — 就像你在 Netflix 或 Steam 上看到的那样 — 还能用六款主题（或你自己的壁纸）来装扮它。底层是久经考验的 **libtorrent** 引擎，所以它不是中看不中用的玩具：而是一个恰好还有点品味的真正客户端。

> **无广告。无遥测。无「Pro」版。无需账号。** 它唯一会自行发起的请求是 GitHub 更新检查，而且可以关闭。源代码就在这里 — 阅读 [`updater.cpp`](src/app/updater.cpp)，自己来验证。

<img src="https://capsule-render.vercel.app/api?type=rect&color=dc2626&height=3&width=100%25" width="100%"/>

## 本分支的不同之处

本分支基于原版 BATorrent **v4.1.0**，加入了一批修复和易用性改进。本节以下的内容描述的是原版应用，同样适用于本分支。

- **重命名一步到位。** 重命名一个种子现在会同时更新磁盘上的文件或文件夹 *以及* 列表中显示的名称，之后还会清理掉旧的空文件夹。按 **F2** 即可重命名；对话框会自动聚焦输入框，按 Enter 确认。
- **删除更可靠。** 删除现在会处理整个多选（而不只是最后点选的那一项）；当开启「同时删除文件」时会从磁盘移除顶层文件夹；对仍在下载中的种子，会先停止再可靠地删除。
- **重构的首选项。** 独立的 **下载** 选项卡；浏览后会刷新的可编辑路径字段；「移动已添加的 `.torrent` 文件」选项和「添加后删除 `.torrent` 文件」选项（取代旧的隐藏 `.processed` 文件夹）；应用图标旁的 **重启** 按钮；以及当监视文件夹可能把你刚删除的种子悄悄重新添加时的提醒。
- **Windows 托盘菜单可用。** 系统托盘图标在 Windows 上现在有右键菜单（显示、打开种子/磁力、全部暂停/恢复、首选项、退出）。
- **细节打磨。** 与应用主题一致的设置/提示对话框，「关于」对话框带默认的 **关闭** 按钮，以及对英文文案的梳理。

> [!NOTE]
> 本分支有两个已知限制：目前仅提供 **Windows** 构建（官方的跨平台版本来自上游），且内置更新检查仍然查询 **原版** 项目的发布，因此不会把本分支的版本标记为可更新。

<img src="https://capsule-render.vercel.app/api?type=rect&color=dc2626&height=3&width=100%25" width="100%"/>

## 为什么会有这个项目

*以下部分出自原作者 Mateus Cruz：*

我是巴西的一名独立开发者。我想要一个认真对待隐私、在每个桌面平台上原生运行、而且看起来不像 2009 年做的 BT 客户端 — 既然找不到，我就自己做了一个。它免费且采用 **MIT 许可**：没有附加条件，不会日后偷偷加入遥测，也不会被悄悄卖给一家加塞广告的公司。支持八种语言，因为「好用」不应该意味着「只有英文」。

## 外观

<p align="center">
  <img src="src/images/themes.gif" alt="在内置主题之间切换" width="860">
</p>

<p align="center">
  <img src="src/images/shot-grid.jpg" alt="Cover-art grid" width="860">
</p>

<p align="center">
  <img src="src/images/shot-list.jpg" alt="List view" width="860">
</p>

<p align="center">
  <img src="src/images/shot-theme.jpg" alt="Sakura theme" width="860">
</p>

- **自动封面** — 它读取种子名称，把真实海报（电影和剧集来自 TMDB，游戏来自 IGDB）拉取到网格视图。一键切换到紧凑列表。
- **六款主题** — Dark、Light、Midnight、Sakura、Dark Star，以及一个完全 **自定义** 的主题（你自己的背景 + 强调色），每款都可选动漫风格的点缀插画。
- 实时速度图、按状态着色的进度、带实时速度和剩余时间的托盘弹窗 — 这些细节让它*感觉*完整。

## 它到底能做什么

| | |
|---|---|
| 🔒 **隐私优先** | 绑定到 VPN 网络接口 + **断网保护（kill switch）**（隧道断开即切断所有流量）、面向私有站（PT）的 PT 模式、Tor 预设、匿名握手、屏蔽迅雷/QQ 等吸血客户端 |
| 🔎 **查找与添加** | 内置搜索（含开放的 CIS/RuTor 源，无需登录）、智能粘贴（Ctrl+V 识别 magnet / `.torrent` / `thunder://` / 哈希）、带正则过滤的 RSS 自动下载、拖放 |
| 📱 **随处掌控** | 浏览器 WebUI + **二维码配对** — 用手机扫一扫，无需手输 IP。二维码在本地生成，你的地址绝不离开本机 |
| 📺 **观看与整理** | 边下边播、自动解压压缩包、分类 + 标签、完成时刷新 Plex/Jellyfin/Emby 媒体库 |
| 🔔 **保持知情** | 原生桌面通知、Telegram 提醒、Discord Rich Presence（「正在下载 X · 67%」） |

<details>
<summary><b>……以及长尾功能</b>（点击展开）</summary>

单文件优先级 · 顺序下载 · 自动注入 Tracker · 内容布局控制 · 排除文件正则 · 临时下载目录 · 带做种时长窗口的「已完成」状态 · 文件出错时自动暂停 · 全局 + 单种子的分享率/时间限制 · 带宽计划（按小时 + 按星期）· 从 qBittorrent 导入 · 创建 `.torrent` 文件 · 种子检查器 · IP 屏蔽列表 · 协议加密 · Gitee 更新镜像 · 完成后自动关机 · Windows Defender 排除 · 完整备份/恢复 · 最近删除历史 · 强制开始 · 内置日志查看器 + 诊断 + IP 泄漏测试 · 按区域设置格式化 · 键盘快捷键。

</details>

<img src="https://capsule-render.vercel.app/api?type=rect&color=dc2626&height=3&width=100%25" width="100%"/>

## 获取

**本分支** 只提供一个构建：Windows 的 alpha 安装程序。

| | | |
|---|---|---|
| **本分支（Windows）** | [`v4.1.0a` 安装程序](https://github.com/coex177/BATorrent/releases/latest)（`BATorrent-setup-x86_64.exe`）。按用户安装，无需管理员权限。 | Windows 10/11 · x86_64 · **alpha** |

需要 **官方、已签名、跨平台** 的构建，请改用原版项目：

| 平台 | | |
|---|---|---|
| **Windows** | [Microsoft Store](https://apps.microsoft.com/detail/9n4l3tq24rc6) · [安装版](https://github.com/BATorrent-app/BATorrent/releases/latest) · [便携版](https://github.com/BATorrent-app/BATorrent/releases/latest) | Windows 10+ |
| **macOS** | **`brew install --cask Mateuscruz19/batorrent/batorrent`** · [`.dmg`](https://github.com/BATorrent-app/BATorrent/releases/latest) | macOS 12+ · Apple Silicon |
| **Linux** | [AppImage](https://github.com/BATorrent-app/BATorrent/releases/latest) | glibc 2.35+ |

然后把 `.torrent` 文件或 magnet 链接拖到窗口里就行。就这么简单。

<sub>**macOS：** 尚未进行公证（Apple 的开发者计划需付费）。Homebrew 最省心 — `brew` 会移除隔离标记，应用直接打开，不会弹 Gatekeeper 提示。若用 `.dmg`，首次请右键 → **打开**。</sub>

<img src="https://capsule-render.vercel.app/api?type=rect&color=dc2626&height=3&width=100%25" width="100%"/>

<details>
<summary><b>从源码构建与工程说明</b></summary>

### 依赖
C++17 · CMake 3.16+ · Qt 6（`Widgets`、`Network`、`Svg`、`Multimedia`）· libtorrent-rasterbar 2.0+ · Boost · Qt6Keychain（可选）。

```bash
# Debian / Ubuntu
sudo apt install build-essential cmake qt6-base-dev qt6-svg-dev qt6-multimedia-dev \
    libtorrent-rasterbar-dev libboost-dev libssl-dev
cmake -B build -DCMAKE_BUILD_TYPE=Release && cmake --build build -j && ./build/BATorrent
```
（macOS：`brew install qt libtorrent-rasterbar boost openssl`。Windows：Qt 安装器 + `vcpkg install libtorrent:x64-windows`。）

### 质量与安全

<p>
  <a href="https://github.com/BATorrent-app/BATorrent/actions/workflows/codeql.yml"><img alt="CodeQL" src="https://github.com/BATorrent-app/BATorrent/actions/workflows/codeql.yml/badge.svg"></a>
  <a href="https://github.com/BATorrent-app/BATorrent/actions/workflows/sanitizers.yml"><img alt="Sanitizers" src="https://github.com/BATorrent-app/BATorrent/actions/workflows/sanitizers.yml/badge.svg"></a>
  <a href="https://sonarcloud.io/summary/new_code?id=Mateuscruz19_BAT-Torrent"><img alt="Quality Gate" src="https://sonarcloud.io/api/project_badges/measure?project=Mateuscruz19_BAT-Torrent&metric=alert_status"></a>
  <a href="https://www.codefactor.io/repository/github/mateuscruz19/batorrent"><img alt="CodeFactor" src="https://www.codefactor.io/repository/github/mateuscruz19/batorrent/badge"></a>
  <a href="https://www.bestpractices.dev/projects/13073"><img alt="OpenSSF Best Practices" src="https://www.bestpractices.dev/projects/13073/badge"></a>
</p>

- **测试** — 每次 CI 构建都运行 Catch2 测试套件（单元、安全、内存）；新的后端行为都会配测试。
- **Sanitizers** — 在 AddressSanitizer + UndefinedBehaviorSanitizer 下干净通过（0 泄漏 / use-after-free / UB）。
- **审查** — 每次发布前都会检查内存/线程安全、WebUI 鉴权、注入、路径穿越、输入校验和密钥处理。密钥保存在系统钥匙串中，绝不明文存储；只有在你设置密码后，WebUI 才会对网络开放。

</details>

## 参与贡献

**本分支特有** 的问题，请到 [coex177/BATorrent](https://github.com/coex177/BATorrent/issues) 提 Issue。原版应用的问题请使用[上游仓库](https://github.com/BATorrent-app/BATorrent)。报告 Bug 时请附上你的平台 + 版本（`帮助 → 关于`）和复现步骤。

## 许可证

[MIT](LICENSE) © 2024–2026 Mateus Cruz（原作者）· 于巴西制作 🦇

本分支由 [coex177](https://github.com/coex177) 维护，仍采用相同的 MIT 许可。
