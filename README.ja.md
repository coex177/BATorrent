> [!IMPORTANT]
> **これは非公式のフォークです。** これは [**coex177**](https://github.com/coex177) の個人フォークであり、公式プロジェクトではありません。upstream を追従しつつ、いくつかの修正と使い勝手の改善を加えています（[このフォークの変更点](#このフォークの変更点)を参照）。原作者とは無関係で、支援・承認も受けていません。
>
> - **オリジナルのプロジェクト:** Mateus Cruz による [BATorrent-app/BATorrent](https://github.com/BATorrent-app/BATorrent)。公式・クロスプラットフォーム・署名済みのビルド（Microsoft Store / Homebrew / AppImage）はこちらを使ってください。
> - **このフォークのビルド:** [coex177/BATorrent のリリース](https://github.com/coex177/BATorrent/releases)。現状は **Windows 専用のアルファ版**（`v4.1.0a`）です。

<p align="center">
  <a href="README.md">English</a> | <a href="README.pt-BR.md">Português</a> | <a href="README.zh-CN.md">中文</a> | <b>日本語</b> | <a href="README.ru.md">Русский</a> | <a href="README.es.md">Español</a> | <a href="README.de.md">Deutsch</a> | <a href="README.ua.md">Українська</a>
</p>

<p align="center">
  <img src="src/images/logo.svg" alt="BATorrent" width="140">
</p>

<h1 align="center">BATorrent</h1>

<p align="center">
  <i>顔のある BitTorrent クライアント — 映画のカバー、6つのテーマ、広告ゼロ。</i>
</p>

<p align="center">
  <a href="https://github.com/coex177/BATorrent/releases"><img alt="Fork release" src="https://img.shields.io/github/v/release/coex177/BATorrent?include_prereleases&style=flat-square&color=dc2626&label=fork%20release"></a>
  <a href="https://github.com/coex177/BATorrent/releases"><img alt="Downloads" src="https://img.shields.io/github/downloads/coex177/BATorrent/total?style=flat-square&color=dc2626"></a>
  <a href="LICENSE"><img alt="License" src="https://img.shields.io/github/license/coex177/BATorrent?style=flat-square&color=dc2626"></a>
  <img alt="Fork build" src="https://img.shields.io/badge/fork%20build-Windows%20x86__64%20·%20alpha-dc2626?style=flat-square">
</p>


<p align="center">
  <img src="src/images/shot-grid-v43.jpg" alt="BATorrent — 開いてすぐ使える、カバーは自動で表示" width="860">
</p>

たいていのトレントクライアントは納税申告書みたいな見た目です。これはダウンロードを **映画・ドラマ・ゲームのカバーの壁** として見せます — Netflix や Steam で見慣れたあの感じ — そして6つのテーマ（あるいは自分の壁紙）で着せ替えできます。中身は実績ある **libtorrent** エンジンなので、見た目だけのおもちゃではありません。たまたまセンスも持ち合わせた、本物のクライアントです。

> **広告なし。テレメトリなし。「Pro」版なし。アカウント不要。** 自分から行う唯一の通信は GitHub の更新確認だけで、それもオフにできます。ソースはここにあります — [`updater.cpp`](src/services/integrations/updater.cpp) を読んで自分で確かめてください。


## このフォークの変更点

このフォークはオリジナルの BATorrent **v4.1.0** をベースに、いくつかの修正と使い勝手の改善を加えたものです。このセクションより下の内容はオリジナルのアプリの説明で、フォークにもそのまま当てはまります。

- **名前変更がすべてを処理。** トレントの名前変更が、ディスク上のファイルまたはフォルダー *と* リストに表示される名前の両方を更新し、空になった古いフォルダーも後片付けします。**F2** で名前変更でき、ダイアログは入力欄にフォーカスして Enter で確定します。
- **削除が確実に。** 削除が複数選択をすべて処理するようになり（最後にクリックした項目だけではありません）、「ファイルも削除」がオンのときはディスク上の最上位フォルダーも削除し、まだアクティブにダウンロード中のトレントも、先に停止してから確実に削除します。
- **設定の再構成。** 専用の **ダウンロード** タブ、参照後に更新される編集可能なパス欄、「追加した `.torrent` ファイルを移動」オプションと「追加後に `.torrent` ファイルを削除」オプション（旧来の隠し `.processed` フォルダーを置き換え）、アプリアイコン横の **再起動** ボタン、そして監視フォルダーが削除したばかりのトレントを黙って再追加しかねない場合の注意表示を追加。
- **Windows でトレイメニューが機能。** システムトレイのアイコンに Windows で右クリックメニューが付きました（表示、トレント/マグネットを開く、すべて一時停止/再開、設定、終了）。
- **仕上げ。** アプリのテーマに合わせた設定・入力ダイアログ、デフォルトで **閉じる** ボタンを持つバージョン情報ダイアログ、英語テキストの見直し。

> [!NOTE]
> このフォークの既知の制限が2つあります。ビルドは今のところ **Windows 専用** で（公式のクロスプラットフォーム版は upstream から提供されます）、内蔵のアップデーターは依然として **オリジナル** プロジェクトのリリースを確認するため、このフォークのバージョンを更新として通知しません。

<img src="https://capsule-render.vercel.app/api?type=rect&color=dc2626&height=3&width=100%25" width="100%"/>

## なぜ作ったのか

*以下のセクションは原作者 Mateus Cruz によるものです:*

私はブラジルの個人開発者です。プライバシーを真剣に扱い、どのデスクトップでもネイティブに動き、2009年製のような見た目ではないトレントクライアントが欲しかった — でも見つからなかったので、自分で作りました。無料で **MIT ライセンス** です。隠れた条件もなく、後からテレメトリが忍び込むこともなく、広告を付け足す会社にこっそり売られることもありません。8つの言語に対応 — 「使える」が「英語だけ」を意味すべきではないからです。

## 見た目

<p align="center">
  <img src="src/images/themes.gif" alt="内蔵テーマの切り替え" width="860">
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

- **自動カバーアート** — トレント名を読み取り、本物のポスター（映画・ドラマは TMDB、ゲームは IGDB）をグリッド表示に取り込みます。1クリックでコンパクトなリスト表示に切り替え。
- **6つのテーマ** — Dark、Light、Midnight、Sakura、Dark Star、そして完全 **カスタム**（自分の背景 + アクセントカラー）。それぞれ任意のアニメ風アクセントアート付き。
- リアルタイムの速度グラフ、状態で色分けされた進捗、ライブ速度と残り時間を表示するトレイポップアップ — *完成された* と感じさせる細部です。

## 実際にできること

| | |
|---|---|
| 🔒 **プライバシー最優先** | VPN インターフェイスへのバインド + **キルスイッチ**（トンネルが落ちたら全通信を遮断）、プライベートトラッカー向け PT モード、Tor プリセット、匿名ハンドシェイク、リーチャー（吸血）ブロック |
| 🔎 **探して追加** | 内蔵検索（CIS/RuTor のオープンソース含む、ログイン不要）、スマートペースト（Ctrl+V で magnet / `.torrent` / `thunder://` / hash）、正規表現フィルタ付き RSS 自動ダウンロード、ドラッグ＆ドロップ |
| 📱 **どこからでも操作** | ブラウザ WebUI と **QR ペアリング** — スマホでスキャンするだけ、IP 入力不要。QR はローカル生成で、アドレスが端末から出ることはありません |
| 📺 **視聴と整理** | ダウンロード中の再生、アーカイブの自動展開、カテゴリ + タグ、完了時に Plex/Jellyfin/Emby のライブラリを更新 |
| 🔔 **見逃さない** | ネイティブのデスクトップ通知、Telegram アラート、Discord リッチプレゼンス（「X をダウンロード中 · 67%」） |

<details>
<summary><b>…そしてロングテール</b>（クリックで展開）</summary>

ファイル別の優先度 · 順次ダウンロード · トラッカー自動追加 · コンテンツ配置の制御 · 除外ファイルの正規表現 · 一時ダウンロード先 · シード期間付きの「完了」状態 · ファイルエラー時の自動一時停止 · 全体 + トレント別のレシオ/時間制限 · 帯域スケジューラ（時間 + 曜日）· qBittorrent からのインポート · `.torrent` ファイル作成 · トレントインスペクタ · IP ブロックリスト · プロトコル暗号化 · Gitee 更新ミラー · 完了時の自動シャットダウン · Windows Defender 除外 · 完全バックアップ/復元 · 最近削除した履歴 · 強制開始 · 内蔵ログビューア + 診断 + IP リークテスト · ロケール対応の書式 · キーボードショートカット。

</details>


## エンジン

多くの torrent アプリは標準の libtorrent をそのままリンクします。BATorrent は小さな**パッチ適用フォーク**を同梱し、公開 API では届かないエンジンの挙動を変更しています。

- **パイプラインの立ち上がりが速い。** 高帯域・高遅延の回線では、標準のリクエストパイプラインは 1 段ずつしか伸びません。フォークではこれを幾何級数的に伸ばし、太い回線をわずかな往復で埋めます。プロジェクト独自の A/B ベンチマークで高速回線で約 **+27%** を計測。標準版のような実行ごとの失速がなく、性能が下がることもありません。
- **同一国の peer を優先。** オフラインの GeoIP データベース（db-ip Lite）が各 peer を国で分類し、フォークの peer ランキングは選択の余地があるとき自国の peer を優先します。多くの場合これは、低遅延で、帯域制限を受けやすい国際経路が減ることを意味します。

どちらもフォークのコンパイル時機能（標準ビルドでは無効）で、埋め込みコピーではなく [`third_party/patches/`](third_party/patches) 配下のバージョン管理されたパッチとして適用されます。

## 入手

**このフォーク** が提供するビルドは1つだけ、Windows 向けのアルファ版インストーラーです。

| | | |
|---|---|---|
| **このフォーク（Windows）** | [`v4.1.0a` インストーラー](https://github.com/coex177/BATorrent/releases/latest)（`BATorrent-setup-x86_64.exe`）。ユーザー単位でインストール、管理者権限不要。 | Windows 10/11 · x86_64 · **アルファ** |

**公式・署名済み・クロスプラットフォーム** のビルドは、オリジナルのプロジェクトを使ってください:

| プラットフォーム | | |
|---|---|---|
| **Windows** | [Microsoft Store](https://apps.microsoft.com/detail/9n4l3tq24rc6) · [インストーラー](https://github.com/BATorrent-app/BATorrent/releases/latest) · [ポータブル版](https://github.com/BATorrent-app/BATorrent/releases/latest) | Windows 10+ |
| **macOS** | **`brew install --cask Mateuscruz19/batorrent/batorrent`** · [`.dmg`](https://github.com/BATorrent-app/BATorrent/releases/latest) | macOS 12+ · Apple Silicon |
| **Linux** | [AppImage](https://github.com/BATorrent-app/BATorrent/releases/latest) | glibc 2.35+ |

あとは `.torrent` か magnet をウィンドウにドロップするだけ。それだけです。

<sub>**macOS:** まだ公証（notarization）されていません（Apple の開発者プログラムは有料のため）。Homebrew が最もスムーズです — `brew` が隔離フラグを外すので、Gatekeeper のダイアログなしで開きます。`.dmg` の場合は初回のみ右クリック → **開く**。</sub>


<details>
<summary><b>ソースからのビルドと技術メモ</b></summary>

### 必要環境
C++17 · CMake 3.16+ · Qt 6（`Widgets`, `Network`, `Svg`, `Multimedia`）· libtorrent-rasterbar 2.0+ · Boost · Qt6Keychain（任意）。

```bash
# Debian / Ubuntu
sudo apt install build-essential cmake qt6-base-dev qt6-svg-dev qt6-multimedia-dev \
    libtorrent-rasterbar-dev libboost-dev libssl-dev
cmake -B build -DCMAKE_BUILD_TYPE=Release && cmake --build build -j && ./build/BATorrent
```
（macOS: `brew install qt libtorrent-rasterbar boost openssl`。Windows: Qt インストーラー + `vcpkg install libtorrent:x64-windows`。）

### 品質とセキュリティ

<p>
  <a href="https://github.com/BATorrent-app/BATorrent/actions/workflows/codeql.yml"><img alt="CodeQL" src="https://github.com/BATorrent-app/BATorrent/actions/workflows/codeql.yml/badge.svg"></a>
  <a href="https://github.com/BATorrent-app/BATorrent/actions/workflows/sanitizers.yml"><img alt="Sanitizers" src="https://github.com/BATorrent-app/BATorrent/actions/workflows/sanitizers.yml/badge.svg"></a>
  <a href="https://sonarcloud.io/summary/new_code?id=Mateuscruz19_BAT-Torrent"><img alt="Quality Gate" src="https://sonarcloud.io/api/project_badges/measure?project=Mateuscruz19_BAT-Torrent&metric=alert_status"></a>
  <a href="https://www.codefactor.io/repository/github/mateuscruz19/batorrent"><img alt="CodeFactor" src="https://www.codefactor.io/repository/github/mateuscruz19/batorrent/badge"></a>
  <a href="https://www.bestpractices.dev/projects/13073"><img alt="OpenSSF Best Practices" src="https://www.bestpractices.dev/projects/13073/badge"></a>
</p>

- **テスト** — すべての CI ビルドで Catch2 スイート（ユニット・セキュリティ・メモリ）。新しいバックエンドの挙動にはテストを追加。
- **サニタイザ** — AddressSanitizer + UndefinedBehaviorSanitizer でクリーンに通過（リーク / use-after-free / UB ゼロ）。
- **レビュー** — 各リリース前にメモリ/スレッド安全性、WebUI 認証、インジェクション、パストラバーサル、入力検証、シークレット管理を確認。シークレットは OS のキーチェーンに保存され、平文にはなりません。WebUI はパスワードを設定して初めてネットワークに公開されます。

</details>

## 貢献

**このフォーク固有** の問題は [coex177/BATorrent](https://github.com/coex177/BATorrent/issues) に Issue を立ててください。オリジナルのアプリについては [upstream のリポジトリ](https://github.com/BATorrent-app/BATorrent) をご利用ください。バグ報告には、プラットフォーム + バージョン（`ヘルプ → バージョン情報`）と再現手順を添えてください。

## ライセンス

[MIT](LICENSE) © 2024–2026 Mateus Cruz（原作者）· made in Brazil 🦇

このフォークは [coex177](https://github.com/coex177) が管理しており、同じ MIT ライセンスのままです。
