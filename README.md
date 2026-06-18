> [!IMPORTANT]
> **This is an unofficial fork.** You're looking at [**coex177**](https://github.com/coex177)'s personal fork of BATorrent, not the official project. It tracks upstream and adds a handful of fixes and quality-of-life features (see [What's different in this fork](#whats-different-in-this-fork)). It is not affiliated with, supported by, or endorsed by the original author.
>
> - **Original project:** [BATorrent-app/BATorrent](https://github.com/BATorrent-app/BATorrent) by Mateus Cruz. Use that for official, cross-platform, signed builds and the Microsoft Store / Homebrew / AppImage releases.
> - **This fork's builds:** [coex177/BATorrent releases](https://github.com/coex177/BATorrent/releases), currently a **Windows-only alpha** (`v4.1.0a`).

<p align="center">
  <b>English</b> | <a href="README.pt-BR.md">Português</a> | <a href="README.zh-CN.md">中文</a> | <a href="README.ja.md">日本語</a> | <a href="README.ru.md">Русский</a> | <a href="README.es.md">Español</a> | <a href="README.de.md">Deutsch</a> | <a href="README.ua.md">Українська</a>
</p>

<p align="center">
  <img src="src/images/logo.svg" alt="BATorrent" width="140">
</p>

<h1 align="center">BATorrent</h1>

<p align="center">
  <i>The BitTorrent client with a face — movie covers, six themes, zero ads.</i>
</p>

<p align="center">
  <a href="https://github.com/coex177/BATorrent/releases"><img alt="Fork release" src="https://img.shields.io/github/v/release/coex177/BATorrent?include_prereleases&style=flat-square&color=dc2626&label=fork%20release"></a>
  <a href="https://github.com/coex177/BATorrent/releases"><img alt="Downloads" src="https://img.shields.io/github/downloads/coex177/BATorrent/total?style=flat-square&color=dc2626"></a>
  <a href="LICENSE"><img alt="License" src="https://img.shields.io/github/license/coex177/BATorrent?style=flat-square&color=dc2626"></a>
  <img alt="Fork build" src="https://img.shields.io/badge/fork%20build-Windows%20x86__64%20·%20alpha-dc2626?style=flat-square">
</p>

<img src="https://capsule-render.vercel.app/api?type=rect&color=dc2626&height=3&width=100%25" width="100%"/>

<p align="center">
  <img src="src/images/with_startup.gif" alt="BATorrent — open and go, covers resolve automatically" width="860">
</p>

Most torrent clients look like a tax form. This one shows your downloads as a **wall of movie, show, and game covers** — the same thing you'd recognise on Netflix or Steam — and lets you dress it in six themes (or your own wallpaper). Under the hood it's the battle-tested **libtorrent** engine, so it's not a pretty toy: it's a real client that just happens to have taste.

> **No ads. No telemetry. No "Pro" tier. No account.** The only request it makes on its own is the GitHub update check, and you can turn that off. The source is right here — read [`updater.cpp`](src/app/updater.cpp) and see for yourself.

<img src="https://capsule-render.vercel.app/api?type=rect&color=dc2626&height=3&width=100%25" width="100%"/>

## What's different in this fork

This fork is based on the original BATorrent **v4.1.0** and adds a batch of fixes and quality-of-life changes. Everything else below this section describes the original app and applies to the fork too.

- **Rename does the whole job.** Renaming a torrent now updates the on-disk file or folder *and* the name shown in the list, and the old empty folder gets cleaned up afterward. Press **F2** to rename; the dialog focuses the field and accepts on Enter.
- **Remove is reliable.** Deleting now handles the entire multi-selection (not just the last item you clicked), removes the top-level folder from disk when "also delete files" is on, and reliably deletes torrents that are still actively downloading by stopping them first.
- **Reworked Preferences.** A dedicated **Downloads** tab; editable path fields that refresh after Browse; a "Move added `.torrent` files" location and a "Delete `.torrent` file after adding" option (replaces the old hidden `.processed` folder); an app-icon **Restart** button; and a heads-up if the watched folder could silently re-add a torrent you just removed.
- **Working Windows tray menu.** The system-tray icon now has a right-click menu on Windows (Show, Open torrent/magnet, Pause/Resume all, Preferences, Quit).
- **Polish.** Skinned settings/prompt dialogs that match the app theme, an About dialog with a default **Close** button, and a cleanup pass over the English strings.

> [!NOTE]
> Two known limitations of this fork: builds are **Windows-only** right now (the official cross-platform releases come from upstream), and the in-app auto-updater still checks the **original** project's releases, so it won't flag this fork's versions as updates.

<img src="https://capsule-render.vercel.app/api?type=rect&color=dc2626&height=3&width=100%25" width="100%"/>

## Why this exists

*The section below is from the original author, Mateus Cruz:*

I'm one developer in Brazil. I wanted a torrent client that took privacy seriously, ran natively on every desktop, and didn't look like it was built in 2009 — and I couldn't find one, so I built it. It's free and **MIT-licensed**: no strings, no telemetry sneaking in later, and it can't be quietly sold to a company that bolts on ads. Eight languages, because "useful" shouldn't mean "English only."

## The look

<p align="center">
  <img src="src/images/themes.gif" alt="Switching between built-in themes" width="860">
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

<p align="center">
  <img src="src/images/palette-demo.gif" alt="Command palette (Ctrl/⌘+K): fuzzy-find any torrent or action" width="860">
</p>

- **Automatic cover art** — it reads the torrent name and pulls the real poster (movies & shows via TMDB, games via IGDB) into a grid view. One click flips to a tight list.
- **Six themes** — Dark, Light, Midnight, Sakura, Dark Star, and a fully **Custom** one (your own background + accent colours), each with optional anime accent art.
- **Command palette** — Ctrl/⌘+K jumps to any torrent or action: pause all, toggle alt speed, open any page, no mouse needed.
- Real-time speed graph, state-coloured progress, a rich tray popup with live speeds and ETA — the details that make it *feel* finished.

## What it actually does

| | |
|---|---|
| 🔒 **Privacy first** | VPN interface binding + **kill switch** (drops all traffic if the tunnel dies), PT mode for private trackers, Tor preset, anonymous handshake, anti-leecher blocking |
| 🔎 **Find & add** | Built-in search (incl. open CIS/RuTor sources, no login), Smart Paste (magnet / `.torrent` / `thunder://` / hash on Ctrl+V), RSS auto-download with regex filters, drag-and-drop |
| 📱 **Control it anywhere** | Browser WebUI with **QR pairing** — scan from your phone, no typing IPs. The QR is generated locally; your address never leaves the machine |
| 📺 **Watch & organise** | Stream while downloading, auto-extract archives, categories + tags, Plex/Jellyfin/Emby library refresh on completion |
| 🔔 **Stay in the loop** | Native desktop notifications, Telegram alerts, Discord Rich Presence ("Downloading X · 67%") |

<details>
<summary><b>…and the long tail</b> (click to expand)</summary>

Per-file priority · sequential download · auto-tracker injection · content-layout control · excluded-file regex · temp download path · completed-state with seeding windows · auto-pause on file errors · global + per-torrent ratio/time limits · bandwidth scheduler (hour + day) · import from qBittorrent · create `.torrent` files · torrent inspector · IP blocklists · protocol encryption · Gitee update mirror · auto-shutdown when done · Windows Defender exclusion · full backup/restore · recently-removed history · force start · built-in log viewer + diagnostics + IP-leak test · locale-aware formatting · keyboard shortcuts.

</details>

<img src="https://capsule-render.vercel.app/api?type=rect&color=dc2626&height=3&width=100%25" width="100%"/>

## Get it

**This fork** ships one build: a Windows alpha installer.

| | | |
|---|---|---|
| **This fork (Windows)** | [Download the `v4.1.0a` installer](https://github.com/coex177/BATorrent/releases/latest) (`BATorrent-setup-x86_64.exe`). Installs per-user, no admin needed. | Windows 10/11 · x86_64 · **alpha** |

For **official, signed, cross-platform** builds, use the original project instead:

| Platform | | |
|---|---|---|
| **Windows** | [Microsoft Store](https://apps.microsoft.com/detail/9n4l3tq24rc6) · [Installer](https://batorrent.com/win) · [Portable](https://batorrent.com/portable) | Windows 10+ |
| **macOS** | **`brew install --cask Mateuscruz19/batorrent/batorrent`** · [`.dmg`](https://batorrent.com/mac) | macOS 12+ · Apple Silicon |
| **Linux** | [AppImage](https://batorrent.com/linux) | glibc 2.35+ |

Then just drop a `.torrent` or magnet onto the window. That's it.

<sub>**macOS:** not notarised yet (Apple's dev program is paid). Homebrew is the smoothest path — `brew` strips the quarantine flag, so it opens with no Gatekeeper prompt. With the `.dmg`, right-click → **Open** the first time.</sub>

<img src="https://capsule-render.vercel.app/api?type=rect&color=dc2626&height=3&width=100%25" width="100%"/>

<details>
<summary><b>Build from source & engineering notes</b></summary>

### Requirements
C++17 · CMake 3.16+ · Qt 6 (`Widgets`, `Network`, `Svg`, `Multimedia`) · libtorrent-rasterbar 2.0+ · Boost · optional Qt6Keychain.

```bash
# Debian / Ubuntu
sudo apt install build-essential cmake qt6-base-dev qt6-svg-dev qt6-multimedia-dev \
    libtorrent-rasterbar-dev libboost-dev libssl-dev
cmake -B build -DCMAKE_BUILD_TYPE=Release && cmake --build build -j && ./build/BATorrent
```
(macOS: `brew install qt libtorrent-rasterbar boost openssl`. Windows: Qt installer + `vcpkg install libtorrent:x64-windows`.)

### Quality & security

<p>
  <a href="https://github.com/BATorrent-app/BATorrent/actions/workflows/codeql.yml"><img alt="CodeQL" src="https://github.com/BATorrent-app/BATorrent/actions/workflows/codeql.yml/badge.svg"></a>
  <a href="https://github.com/BATorrent-app/BATorrent/actions/workflows/sanitizers.yml"><img alt="Sanitizers" src="https://github.com/BATorrent-app/BATorrent/actions/workflows/sanitizers.yml/badge.svg"></a>
  <a href="https://sonarcloud.io/summary/new_code?id=Mateuscruz19_BAT-Torrent"><img alt="Quality Gate" src="https://sonarcloud.io/api/project_badges/measure?project=Mateuscruz19_BAT-Torrent&metric=alert_status"></a>
  <a href="https://www.codefactor.io/repository/github/mateuscruz19/batorrent"><img alt="CodeFactor" src="https://www.codefactor.io/repository/github/mateuscruz19/batorrent/badge"></a>
  <a href="https://www.bestpractices.dev/projects/13073"><img alt="OpenSSF Best Practices" src="https://www.bestpractices.dev/projects/13073/badge"></a>
</p>

- **Tests** — Catch2 suite (unit, security, memory) on every CI build; new backend behaviour gets a test.
- **Sanitizers** — passes clean under AddressSanitizer + UndefinedBehaviorSanitizer (0 leaks / UAF / UB).
- **Reviewed** before each release for memory/thread safety, WebUI auth, injection, path traversal, input validation, and secret handling. Secrets live in the OS keychain, never plaintext; the WebUI only binds to the network once you set a password.

</details>

## Contributing

For issues with **this fork specifically**, open them on [coex177/BATorrent](https://github.com/coex177/BATorrent/issues). For the original app, please use the [upstream repo](https://github.com/BATorrent-app/BATorrent). Bug reports: include your platform + version (`Help → About`) and steps to reproduce.

## License

[MIT](LICENSE) © 2024–2026 Mateus Cruz (original author) · made in Brazil 🦇

This fork is maintained by [coex177](https://github.com/coex177) and remains under the same MIT license.
