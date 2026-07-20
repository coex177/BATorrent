> [!IMPORTANT]
> **Dies ist ein inoffizieller Fork.** Du siehst den persönlichen Fork von [**coex177**](https://github.com/coex177), nicht das offizielle Projekt. Er folgt dem Upstream und ergänzt eine Handvoll Fixes und Komfortfunktionen (siehe [Was in diesem Fork anders ist](#was-in-diesem-fork-anders-ist)). Er ist nicht mit dem ursprünglichen Autor verbunden und wird von ihm weder unterstützt noch befürwortet.
>
> - **Originalprojekt:** [BATorrent-app/BATorrent](https://github.com/BATorrent-app/BATorrent) von Mateus Cruz. Nutze es für offizielle, plattformübergreifende, signierte Builds (Microsoft Store / Homebrew / AppImage).
> - **Builds dieses Forks:** [Releases von coex177/BATorrent](https://github.com/coex177/BATorrent/releases), derzeit eine **Windows-only-Alpha** (`v4.1.0a`).

<p align="center">
  <a href="README.md">English</a> | <a href="README.pt-BR.md">Português</a> | <a href="README.zh-CN.md">中文</a> | <a href="README.ja.md">日本語</a> | <a href="README.ru.md">Русский</a> | <a href="README.es.md">Español</a> | <b>Deutsch</b> | <a href="README.ua.md">Українська</a>
</p>

<p align="center">
  <img src="src/images/logo.svg" alt="BATorrent" width="140">
</p>

<h1 align="center">BATorrent</h1>

<p align="center">
  <i>Der BitTorrent-Client mit Gesicht — Filmcover, sechs Themes, null Werbung.</i>
</p>

<p align="center">
  <a href="https://github.com/coex177/BATorrent/releases"><img alt="Fork release" src="https://img.shields.io/github/v/release/coex177/BATorrent?include_prereleases&style=flat-square&color=dc2626&label=fork%20release"></a>
  <a href="https://github.com/coex177/BATorrent/releases"><img alt="Downloads" src="https://img.shields.io/github/downloads/coex177/BATorrent/total?style=flat-square&color=dc2626"></a>
  <a href="LICENSE"><img alt="License" src="https://img.shields.io/github/license/coex177/BATorrent?style=flat-square&color=dc2626"></a>
  <img alt="Fork build" src="https://img.shields.io/badge/fork%20build-Windows%20x86__64%20·%20alpha-dc2626?style=flat-square">
</p>


<p align="center">
  <img src="src/images/shot-grid-v43.jpg" alt="BATorrent — öffnen und loslegen, Cover werden automatisch geladen" width="860">
</p>

Die meisten Torrent-Clients sehen aus wie ein Steuerformular. Dieser zeigt deine Downloads als **Wand aus Film-, Serien- und Spielcovern** — dasselbe, was du von Netflix oder Steam kennst — und lässt sich in sechs Themes (oder dein eigenes Hintergrundbild) kleiden. Unter der Haube steckt die bewährte **libtorrent**-Engine, also kein hübsches Spielzeug: ein echter Client, der zufällig auch Geschmack hat.

> **Keine Werbung. Keine Telemetrie. Keine „Pro"-Stufe. Kein Konto.** Die einzige Anfrage, die er von sich aus stellt, ist die GitHub-Update-Prüfung, und die kannst du abschalten. Der Quellcode ist direkt hier — lies [`updater.cpp`](src/services/integrations/updater.cpp) und überzeug dich selbst.


## Was in diesem Fork anders ist

Dieser Fork basiert auf dem originalen BATorrent **v4.1.0** und ergänzt eine Reihe von Fixes und Komfortverbesserungen. Alles unterhalb dieses Abschnitts beschreibt die Original-App und gilt auch für den Fork.

- **Umbenennen erledigt alles.** Das Umbenennen eines Torrents aktualisiert jetzt die Datei oder den Ordner auf der Festplatte *und* den in der Liste angezeigten Namen, und der alte leere Ordner wird danach aufgeräumt. Drücke **F2** zum Umbenennen; der Dialog fokussiert das Feld und bestätigt mit Enter.
- **Entfernen ist zuverlässig.** Das Löschen behandelt jetzt die gesamte Mehrfachauswahl (nicht nur das zuletzt angeklickte Element), entfernt den obersten Ordner von der Festplatte, wenn "Dateien ebenfalls löschen" aktiv ist, und löscht zuverlässig Torrents, die noch aktiv herunterladen, indem es sie zuerst stoppt.
- **Überarbeitete Einstellungen.** Ein eigener Tab **Downloads**; editierbare Pfadfelder, die nach dem Durchsuchen aktualisieren; eine Option "Hinzugefügte `.torrent`-Dateien verschieben" und eine Option "`.torrent`-Datei nach dem Hinzufügen löschen" (ersetzt den alten versteckten `.processed`-Ordner); eine **Neustart**-Schaltfläche beim App-Icon; und ein Hinweis, falls der überwachte Ordner einen gerade entfernten Torrent stillschweigend wieder hinzufügen könnte.
- **Funktionierendes Tray-Menü unter Windows.** Das Symbol im System-Tray hat unter Windows jetzt ein Rechtsklick-Menü (Anzeigen, Torrent/Magnet öffnen, Alle pausieren/fortsetzen, Einstellungen, Beenden).
- **Feinschliff.** Einstellungs- und Eingabedialoge im App-Theme, ein Über-Dialog mit standardmäßiger **Schließen**-Schaltfläche und eine Überarbeitung der englischen Texte.

> [!NOTE]
> Zwei bekannte Einschränkungen dieses Forks: Builds gibt es vorerst **nur für Windows** (die offiziellen plattformübergreifenden Versionen kommen vom Upstream), und der eingebaute Updater prüft weiterhin die Releases des **Originalprojekts**, meldet die Versionen dieses Forks also nicht als Updates.

<img src="https://capsule-render.vercel.app/api?type=rect&color=dc2626&height=3&width=100%25" width="100%"/>

## Warum es das gibt

*Der folgende Abschnitt stammt vom ursprünglichen Autor, Mateus Cruz:*

Ich bin ein einzelner Entwickler in Brasilien. Ich wollte einen Torrent-Client, der Privatsphäre ernst nimmt, nativ auf jedem Desktop läuft und nicht aussieht, als wäre er 2009 gebaut worden — und weil ich keinen fand, habe ich meinen eigenen gebaut. Er ist kostenlos und **MIT-lizenziert**: keine Haken, keine Telemetrie, die sich später einschleicht, und er kann nicht still an eine Firma verkauft werden, die Werbung dranschraubt. Acht Sprachen, denn „nützlich" sollte nicht „nur Englisch" heißen.

## Das Aussehen

<p align="center">
  <img src="src/images/themes.gif" alt="Wechsel zwischen den integrierten Themes" width="860">
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

- **Automatische Cover** — liest den Torrent-Namen und holt das echte Poster (Filme & Serien über TMDB, Spiele über IGDB) in eine Rasteransicht. Ein Klick wechselt zur kompakten Liste.
- **Sechs Themes** — Dark, Light, Midnight, Sakura, Dark Star und ein vollständig **anpassbares** (eigener Hintergrund + Akzentfarben), jeweils mit optionaler Anime-Akzentgrafik.
- Echtzeit-Geschwindigkeitsdiagramm, zustandsgefärbter Fortschritt, ein reichhaltiges Tray-Popup mit Live-Geschwindigkeiten und Restzeit — die Details, die es *fertig* wirken lassen.

## Was er wirklich kann

| | |
|---|---|
| 🔒 **Privatsphäre zuerst** | VPN-Interface-Bindung + **Kill Switch** (kappt allen Verkehr, wenn der Tunnel abbricht), PT-Modus für private Tracker, Tor-Voreinstellung, anonymer Handshake, Anti-Leecher-Blockade |
| 🔎 **Finden & hinzufügen** | Integrierte Suche (inkl. offene CIS/RuTor-Quellen, ohne Login), Smart Paste (Magnet / `.torrent` / `thunder://` / Hash per Strg+V), RSS-Auto-Download mit Regex-Filtern, Drag & Drop |
| 📱 **Von überall steuern** | Browser-WebUI mit **QR-Kopplung** — vom Handy scannen, keine IPs tippen. Der QR-Code wird lokal erzeugt; deine Adresse verlässt den Rechner nie |
| 📺 **Ansehen & ordnen** | Streamen während des Downloads, automatisches Entpacken von Archiven, Kategorien + Tags, Plex/Jellyfin/Emby-Bibliotheksaktualisierung bei Abschluss |
| 🔔 **Auf dem Laufenden bleiben** | Native Desktop-Benachrichtigungen, Telegram-Alerts, Discord Rich Presence („Lädt X · 67%") |

<details>
<summary><b>…und der lange Rest</b> (zum Aufklappen klicken)</summary>

Priorität pro Datei · sequenzieller Download · automatisches Tracker-Einspielen · Inhalts-Layout-Steuerung · Regex für ausgeschlossene Dateien · temporärer Download-Pfad · Status „Abgeschlossen" mit Seeding-Fenstern · Auto-Pause bei Dateifehlern · globale + pro-Torrent Ratio-/Zeitlimits · Bandbreiten-Planer (Stunde + Tag) · Import aus qBittorrent · `.torrent`-Dateien erstellen · Torrent-Inspektor · IP-Sperrlisten · Protokollverschlüsselung · Gitee-Update-Mirror · automatisches Herunterfahren nach Abschluss · Windows-Defender-Ausnahme · vollständiges Backup/Restore · Verlauf kürzlich entfernter Torrents · Start erzwingen · integrierter Log-Viewer + Diagnose + IP-Leak-Test · gebietsschema-bewusste Formatierung · Tastenkürzel.

</details>


## Der Motor

Die meisten Torrent-Apps binden das Standard-libtorrent ein. BATorrent liefert einen kleinen **gepatchten Fork** mit und kann so Engine-Verhalten ändern, an das die öffentliche API nicht herankommt:

- **Schnellerer Pipeline-Aufbau.** Auf einer Verbindung mit hoher Bandbreite und hoher Latenz wächst die Standard-Anfrage-Pipeline Schritt für Schritt; der Fork lässt sie geometrisch wachsen und füllt so eine dicke Leitung in einem Bruchteil der Roundtrips. Im projekteigenen A/B-Benchmark rund +27 % auf einer schnellen Verbindung gemessen, ohne die Aussetzer des Standards zwischen den Läufen — und nie langsamer.
- **Bevorzugung von Peers im eigenen Land.** Eine Offline-GeoIP-Datenbank (db-ip Lite) markiert jeden Peer nach Land, und das Peer-Ranking des Forks bevorzugt bei freier Wahl Peers im eigenen Land — das bedeutet meist geringere Latenz und weniger gedrosselte grenzüberschreitende Routen.

Beides sind Compile-Time-Funktionen des Forks (in einem Standard-Build aus) und werden als versionierte Patches unter [`third_party/patches/`](third_party/patches) angewendet, nicht als eingebettete Kopie.

## Holen

**Dieser Fork** liefert genau einen Build: einen Windows-Alpha-Installer.

| | | |
|---|---|---|
| **Dieser Fork (Windows)** | [`v4.1.0a`-Installer](https://github.com/coex177/BATorrent/releases/latest) (`BATorrent-setup-x86_64.exe`). Installation pro Benutzer, ohne Admin-Rechte. | Windows 10/11 · x86_64 · **Alpha** |

Für **offizielle, signierte, plattformübergreifende** Builds nutze stattdessen das Originalprojekt:

| Plattform | | |
|---|---|---|
| **Windows** | [Microsoft Store](https://apps.microsoft.com/detail/9n4l3tq24rc6) · [Installer](https://github.com/BATorrent-app/BATorrent/releases/latest) · [Portabel](https://github.com/BATorrent-app/BATorrent/releases/latest) | Windows 10+ |
| **macOS** | **`brew install --cask Mateuscruz19/batorrent/batorrent`** · [`.dmg`](https://github.com/BATorrent-app/BATorrent/releases/latest) | macOS 12+ · Apple Silicon |
| **Linux** | [AppImage](https://github.com/BATorrent-app/BATorrent/releases/latest) | glibc 2.35+ |

Dann einfach eine `.torrent`-Datei oder einen Magnet auf das Fenster ziehen. Das war's.

<sub>**macOS:** noch nicht notarisiert (Apples Entwicklerprogramm ist kostenpflichtig). Homebrew ist der reibungsloseste Weg — `brew` entfernt das Quarantäne-Flag, sodass die App ohne Gatekeeper-Dialog öffnet. Bei der `.dmg` beim ersten Mal Rechtsklick → **Öffnen**.</sub>


<details>
<summary><b>Aus dem Quellcode bauen & technische Notizen</b></summary>

### Voraussetzungen
C++17 · CMake 3.16+ · Qt 6 (`Widgets`, `Network`, `Svg`, `Multimedia`) · libtorrent-rasterbar 2.0+ · Boost · Qt6Keychain (optional).

```bash
# Debian / Ubuntu
sudo apt install build-essential cmake qt6-base-dev qt6-svg-dev qt6-multimedia-dev \
    libtorrent-rasterbar-dev libboost-dev libssl-dev
cmake -B build -DCMAKE_BUILD_TYPE=Release && cmake --build build -j && ./build/BATorrent
```
(macOS: `brew install qt libtorrent-rasterbar boost openssl`. Windows: Qt-Installer + `vcpkg install libtorrent:x64-windows`.)

### Qualität & Sicherheit

<p>
  <a href="https://github.com/BATorrent-app/BATorrent/actions/workflows/codeql.yml"><img alt="CodeQL" src="https://github.com/BATorrent-app/BATorrent/actions/workflows/codeql.yml/badge.svg"></a>
  <a href="https://github.com/BATorrent-app/BATorrent/actions/workflows/sanitizers.yml"><img alt="Sanitizers" src="https://github.com/BATorrent-app/BATorrent/actions/workflows/sanitizers.yml/badge.svg"></a>
  <a href="https://sonarcloud.io/summary/new_code?id=Mateuscruz19_BAT-Torrent"><img alt="Quality Gate" src="https://sonarcloud.io/api/project_badges/measure?project=Mateuscruz19_BAT-Torrent&metric=alert_status"></a>
  <a href="https://www.codefactor.io/repository/github/mateuscruz19/batorrent"><img alt="CodeFactor" src="https://www.codefactor.io/repository/github/mateuscruz19/batorrent/badge"></a>
  <a href="https://www.bestpractices.dev/projects/13073"><img alt="OpenSSF Best Practices" src="https://www.bestpractices.dev/projects/13073/badge"></a>
</p>

- **Tests** — Catch2-Suite (Unit, Sicherheit, Speicher) bei jedem CI-Build; neues Backend-Verhalten bekommt einen Test.
- **Sanitizers** — läuft sauber unter AddressSanitizer + UndefinedBehaviorSanitizer (0 Lecks / Use-after-free / UB).
- **Geprüft** vor jedem Release auf Speicher-/Thread-Sicherheit, WebUI-Authentifizierung, Injection, Path Traversal, Eingabevalidierung und Umgang mit Geheimnissen. Geheimnisse liegen im OS-Keychain, nie im Klartext; die WebUI öffnet sich erst zum Netzwerk, wenn du ein Passwort setzt.

</details>

## Mitwirken

Für Probleme **speziell mit diesem Fork** eröffne Issues unter [coex177/BATorrent](https://github.com/coex177/BATorrent/issues). Für die Original-App nutze bitte das [Upstream-Repository](https://github.com/BATorrent-app/BATorrent). Fehlerberichte: nenne deine Plattform + Version (`Hilfe → Über`) und die Schritte zur Reproduktion.

## Lizenz

[MIT](LICENSE) © 2024–2026 Mateus Cruz (ursprünglicher Autor) · made in Brazil 🦇

Dieser Fork wird von [coex177](https://github.com/coex177) gepflegt und bleibt unter derselben MIT-Lizenz.
