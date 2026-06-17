// SPDX-License-Identifier: MIT
// BATorrent C++<->QML bridge tests (Catch2 v3)
//
// Covers the qmlposterbridge layer that the QML UI depends on but no other test
// exercised. Runs headless via the "offscreen" platform so the GUI-adjacent
// bridges (clipboard, painter, style hints) construct without a display.

#include <catch2/catch_test_macros.hpp>

#include <QApplication>
#include <QSettings>
#include <QStandardPaths>
#include <QTemporaryDir>
#include <QElapsedTimer>
#include <QEventLoop>
#include <QTimer>
#include <QFile>
#include <QDir>
#include <QFileInfo>
#include <QVariantMap>
#include <QMetaType>

#include <libtorrent/file_storage.hpp>
#include <libtorrent/create_torrent.hpp>
#include <libtorrent/bencode.hpp>

#include "torrent/sessionmanager.h"
#include "app/metadataresolver.h"
#include "app/gamesourcemanager.h"
#include "gui/qmlposterbridge.h"

namespace lt = libtorrent;

// Pump the Qt event loop until pred() holds or the timeout elapses; SessionManager
// adds/renames torrents asynchronously (libtorrent alerts), so reads need to settle.
template <typename Pred>
static bool pumpUntil(Pred pred, int timeoutMs = 8000)
{
    QElapsedTimer t; t.start();
    while (!pred() && t.elapsed() < timeoutMs)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 30);
    return pred();
}

// Build a real, private (offline — no DHT/LSD/PEX) multi-file .torrent under `dir`
// and return its path. Mirrors the create flow in qmlposterbridge.cpp.
static QString makeFixtureTorrent(const QString &dir)
{
    const QString content = dir + "/bat_fixture";
    QDir().mkpath(content + "/sub");
    auto writeN = [](const QString &p, int n) {
        QFile f(p); f.open(QIODevice::WriteOnly); f.write(QByteArray(n, 'x')); f.close();
    };
    writeN(content + "/a.txt", 100);
    writeN(content + "/sub/b.txt", 200);

    lt::file_storage fs;
    lt::add_files(fs, content.toStdString());
    lt::create_torrent ct(fs, 16384, lt::create_torrent::v1_only);   // classic v1 → no v2 pad files
    ct.add_tracker("udp://tracker.test:6969/announce", 0);
    ct.set_priv(true);                                  // private → fully offline
    lt::set_piece_hashes(ct, dir.toStdString());        // parent of "bat_fixture"

    std::vector<char> buf;
    lt::bencode(std::back_inserter(buf), ct.generate());
    const QString out = dir + "/sample.torrent";
    QFile f(out); f.open(QIODevice::WriteOnly);
    f.write(buf.data(), static_cast<qsizetype>(buf.size()));
    f.close();
    return out;
}

// Build a real, private single-file .torrent (no enclosing folder) under `dir`.
static QString makeSingleFileTorrent(const QString &dir)
{
    const QString file = dir + "/single_fixture.bin";
    { QFile f(file); f.open(QIODevice::WriteOnly); f.write(QByteArray(300, 'y')); f.close(); }

    lt::file_storage fs;
    lt::add_files(fs, file.toStdString());
    lt::create_torrent ct(fs, 16384, lt::create_torrent::v1_only);
    ct.add_tracker("udp://tracker.test:6969/announce", 0);
    ct.set_priv(true);
    lt::set_piece_hashes(ct, dir.toStdString());

    std::vector<char> buf;
    lt::bencode(std::back_inserter(buf), ct.generate());
    const QString out = dir + "/single.torrent";
    QFile f(out); f.open(QIODevice::WriteOnly);
    f.write(buf.data(), static_cast<qsizetype>(buf.size()));
    f.close();
    return out;
}

// Reset persisted session state (resume data + the BATorrent settings store) so a
// torrent-adding test starts from an empty session regardless of run order —
// Catch2 randomizes test order and SessionManager saves/loads resume data from a
// process-shared dir, which would otherwise leak torrents between cases.
static void wipeBatState()
{
    QDir(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation)).removeRecursively();
    QSettings s("BATorrent", "BATorrent");
    s.clear();
    s.sync();
}

// A single-file torrent whose content is unique to `tag`, so each call yields a
// distinct info-hash (libtorrent silently ignores a duplicate-hash add).
static QString makeDistinctTorrent(const QString &dir, int tag)
{
    const QString file = dir + QStringLiteral("/file%1.bin").arg(tag);
    { QFile f(file); f.open(QIODevice::WriteOnly);
      f.write(QByteArray(64 + tag * 16, static_cast<char>('a' + tag))); f.close(); }

    lt::file_storage fs;
    lt::add_files(fs, file.toStdString());
    lt::create_torrent ct(fs, 16384, lt::create_torrent::v1_only);
    ct.set_priv(true);
    lt::set_piece_hashes(ct, dir.toStdString());

    std::vector<char> buf;
    lt::bencode(std::back_inserter(buf), ct.generate());
    const QString out = dir + QStringLiteral("/t%1.torrent").arg(tag);
    QFile f(out); f.open(QIODevice::WriteOnly);
    f.write(buf.data(), static_cast<qsizetype>(buf.size()));
    f.close();
    return out;
}

// ============================================================================
//  Headless Qt app singleton (offscreen) + isolated settings store
// ============================================================================
static int   s_argc = 1;
static char  s_arg0[] = "test_bridge";
static char *s_argv[] = { s_arg0, nullptr };

static QApplication &app()
{
    static QApplication *a = [] {
        qputenv("QT_QPA_PLATFORM", "offscreen");
        // Sandbox all paths + settings: empty session, isolated QSettings, never
        // touches (or migrates from) the user's real BATorrent data.
        QStandardPaths::setTestModeEnabled(true);
        // A dedicated org that shares NOTHING with the real app or other test
        // binaries — so wiping our own data dir can never touch real user data or
        // another suite's fixtures.
        QCoreApplication::setOrganizationName("BATorrentBridgeTest");
        QCoreApplication::setApplicationName("BATorrentBridgeTest");
        // Clear only OUR own leaf dirs so every run starts with an empty session
        // and isolated settings (never the parent — that's another suite's space).
        for (auto loc : { QStandardPaths::AppDataLocation, QStandardPaths::AppConfigLocation }) {
            const QString p = QStandardPaths::writableLocation(loc);
            if (!p.isEmpty()) QDir(p).removeRecursively();
        }
        // SessionManager persists to its own explicit org ("BATorrent"), not the
        // test org above — wipe it too so persisted prefs don't leak across runs.
        QSettings("BATorrent", "BATorrent").clear();
        return new QApplication(s_argc, s_argv);
    }();
    return *a;
}

// ============================================================================
//  QmlPairingBridge — the pairing QR (pure: qrcodegen, no session/GUI)
// ============================================================================
TEST_CASE("Pairing: qrRowsForUrl encodes a square binary matrix", "[bridge][pairing]")
{
    app();
    QmlPairingBridge p;

    const QStringList rows = p.qrRowsForUrl(QStringLiteral("http://192.168.0.10:8080/?pair=YWRtaW46cHc"));
    REQUIRE_FALSE(rows.isEmpty());

    const int n = rows.size();
    for (const QString &r : rows) {
        REQUIRE(r.size() == n);                       // square
        for (const QChar c : r)
            REQUIRE((c == QLatin1Char('0') || c == QLatin1Char('1')));   // binary only
    }
}

TEST_CASE("Pairing: encoding is deterministic", "[bridge][pairing]")
{
    app();
    QmlPairingBridge p;
    const QString url = QStringLiteral("http://10.0.0.5:8080/?pair=dXNlcjpzZWNyZXQ");
    REQUIRE(p.qrRowsForUrl(url) == p.qrRowsForUrl(url));
}

TEST_CASE("Pairing: empty URL yields no QR rows", "[bridge][pairing]")
{
    app();
    QmlPairingBridge p;
    REQUIRE(p.qrRowsForUrl(QString()).isEmpty());     // empty/garbage URL → no matrix
}

// ============================================================================
//  QmlThemeBridge — theme name persistence
// ============================================================================
TEST_CASE("Theme: themeName round-trips through settings", "[bridge][theme]")
{
    app();
    QmlThemeBridge t;
    t.setThemeName(QStringLiteral("midnight"));
    REQUIRE(t.themeName() == QStringLiteral("midnight"));

    QmlThemeBridge t2;                                // a fresh bridge reads the persisted value
    REQUIRE(t2.themeName() == QStringLiteral("midnight"));

    t.setThemeName(QStringLiteral("dark"));           // restore default-ish
}

// ============================================================================
//  QmlSessionBridge — selection state with no torrents
// ============================================================================
TEST_CASE("Session bridge: empty session has no selection", "[bridge][session]")
{
    app();
    SessionManager session;
    MetadataResolver resolver;
    QmlSessionBridge bridge(&session, &resolver);

    REQUIRE(bridge.torrentCount() == 0);
    REQUIRE_FALSE(bridge.hasSelection());
    REQUIRE(bridge.selectedName().isEmpty());
    REQUIRE(bridge.selectedFiles().isEmpty());
    REQUIRE(bridge.selectedPeerList().isEmpty());
    REQUIRE(bridge.selectedTrackers().isEmpty());
}

// ============================================================================
//  QmlSearchBridge — "Tudo" aggregates every source into one flat result list
// ============================================================================
TEST_CASE("Search bridge: 'Tudo' merges loaded game catalog synchronously", "[bridge][search]")
{
    app();
    SessionManager session;
    QmlSearchBridge bridge(&session);

    // Pre-load a catalog so the aggregate path resolves without the network.
    const QByteArray cat = R"({"name":"Test","downloads":[
        {"title":"Cyberpunk 2077 [FitGirl Repack]","uris":["magnet:?xt=urn:btih:aaaa"],"fileSize":"58 GB"},
        {"title":"Elden Ring [DODI]","uris":["magnet:?xt=urn:btih:bbbb"],"fileSize":"45 GB"}]})";
    REQUIRE(GameSourceManager::instance().indexCatalog("Test", cat) == 2);

    bridge.search("all", "cyberpunk", 0);

    // Games append synchronously; any torrent providers would arrive later (async),
    // so right after the call only the matching game is present.
    REQUIRE(bridge.mode() == "all");
    const QVariantList results = bridge.results();
    REQUIRE(results.size() == 1);
    CHECK(results[0].toMap().value("name").toString() == "Cyberpunk 2077");
    CHECK(results[0].toMap().value("sub").toString() == "Test");
}

// ============================================================================
//  QmlSettingsBridge — pairing flag derives from QSettings (post-keychain move)
// ============================================================================
TEST_CASE("Settings bridge: pairingActive reflects settings, not the keychain", "[bridge][settings]")
{
    app();
    QSettings st;
    st.setValue("webUiEnabled", false);              // keep the ctor from starting a server
    SessionManager session;
    QmlSettingsBridge bridge(&session);

    REQUIRE(bridge.webUiUser() == QStringLiteral("admin"));
    REQUIRE_FALSE(bridge.pairingActive());

    st.setValue("webUiEnabled", true);
    st.setValue("webUiRemoteAccess", true);
    st.setValue("webUiPasswordHash", QStringLiteral("deadbeef"));
    REQUIRE(bridge.pairingActive());

    st.setValue("webUiPasswordHash", QString());     // no credential → not paired
    REQUIRE_FALSE(bridge.pairingActive());

    st.setValue("webUiEnabled", false);
    st.setValue("webUiRemoteAccess", false);
}

// ============================================================================
//  QmlPosterModel / QmlTorrentFilterProxy — empty-model contract
// ============================================================================
TEST_CASE("Poster model: empty model, roles defined", "[bridge][model]")
{
    app();
    SessionManager session;
    MetadataResolver resolver;
    QmlPosterModel model(&session, &resolver);

    REQUIRE(model.rowCount() == 0);
    REQUIRE_FALSE(model.roleNames().isEmpty());

    QmlTorrentFilterProxy proxy;
    proxy.setSourceModel(&model);
    REQUIRE(proxy.rowCount() == 0);
}

// ============================================================================
//  QmlSessionBridge with a REAL loaded torrent — the methods that need content
// ============================================================================
TEST_CASE("Session bridge: a loaded torrent exposes and mutates files/trackers", "[bridge][session][torrent]")
{
    app();
    QTemporaryDir tmp;
    REQUIRE(tmp.isValid());
    const QString torrentPath = makeFixtureTorrent(tmp.path());
    QDir().mkpath(tmp.path() + "/dl");

    SessionManager session;
    MetadataResolver resolver;
    QmlSessionBridge bridge(&session, &resolver);

    session.addTorrent(torrentPath, tmp.path() + "/dl");
    REQUIRE(pumpUntil([&] { return session.torrentCount() == 1; }));

    bridge.setSelectedRows({0});
    REQUIRE(bridge.hasSelection());

    // --- read side (from the torrent metadata, deterministic once loaded) ---
    REQUIRE_FALSE(bridge.selectedName().isEmpty());
    REQUIRE_FALSE(bridge.selectedHash().isEmpty());
    REQUIRE_FALSE(bridge.selectedSize().isEmpty());

    QVariantList files = bridge.selectedFiles();
    REQUIRE(files.size() == 2);

    const int trackers0 = bridge.selectedTrackers().size();
    REQUIRE(trackers0 >= 1);                              // the tracker baked in at create

    // --- per-file priority ---
    bridge.setSelectedFilePriority(0, 0);                 // Skip file 0
    REQUIRE(pumpUntil([&] {
        return bridge.selectedFiles().value(0).toMap().value("priority").toInt() == 0;
    }));

    // --- add / remove tracker ---
    bridge.addTrackerToSelected("udp://added.test:80/announce");
    REQUIRE(pumpUntil([&] { return bridge.selectedTrackers().size() > trackers0; }));
    bridge.removeTrackerFromSelected("udp://added.test:80/announce");
    REQUIRE(pumpUntil([&] { return bridge.selectedTrackers().size() == trackers0; }));

    // --- rename a file (async libtorrent file_renamed alert) ---
    bridge.renameSelectedFile(0, "renamed_fixture.txt");
    REQUIRE(pumpUntil([&] {
        const QVariantList fl = bridge.selectedFiles();
        for (const QVariant &v : fl)
            if (v.toMap().value("path").toString().contains("renamed_fixture"))
                return true;
        return false;
    }));
}

// ============================================================================
//  QmlSessionBridge — torrent-level rename (renameSelected -> renameTorrent):
//  the on-disk file/folder AND the displayed name change, and the display name
//  override persists. Regression: rename only touched file 0 and never updated
//  the list name; multi-file torrents renamed nothing.
// ============================================================================
TEST_CASE("Session bridge: renaming a multi-file torrent re-roots files + overrides name", "[bridge][session][rename]")
{
    app();
    wipeBatState();
    QTemporaryDir tmp;
    REQUIRE(tmp.isValid());
    const QString torrentPath = makeFixtureTorrent(tmp.path());
    QDir().mkpath(tmp.path() + "/dl");

    SessionManager session;
    MetadataResolver resolver;
    QmlSessionBridge bridge(&session, &resolver);

    session.addTorrent(torrentPath, tmp.path() + "/dl");
    REQUIRE(pumpUntil([&] { return session.torrentCount() == 1; }));
    bridge.setSelectedRows({0});
    REQUIRE(bridge.hasSelection());

    REQUIRE(bridge.selectedName() == "bat_fixture");          // the folder name from create
    const QString hash = session.torrentHashAt(0);            // full hash (selectedHash() is ellipsized for the UI)
    REQUIRE_FALSE(hash.isEmpty());

    bridge.renameSelected("Renamed Collection");

    // Display name override is applied on the synchronous read path...
    REQUIRE(bridge.selectedName() == "Renamed Collection");
    // ...and persisted under the per-torrent names group.
    REQUIRE(QSettings("BATorrent", "BATorrent")
                .value("torrentNames/" + hash).toString() == "Renamed Collection");

    // The top-level folder rename is async (libtorrent rename_file alerts):
    // every file path re-roots under the new folder name.
    REQUIRE(pumpUntil([&] {
        const QVariantList fl = bridge.selectedFiles();
        if (fl.size() != 2) return false;
        for (const QVariant &v : fl)
            if (!v.toMap().value("path").toString().contains("Renamed Collection"))
                return false;
        return true;
    }));
    wipeBatState();   // don't leak this torrent's resume data into the next case
}

TEST_CASE("Session bridge: folder rename moves data into the new folder and prunes the old one", "[bridge][session][rename]")
{
    app();
    wipeBatState();
    QTemporaryDir tmp;
    REQUIRE(tmp.isValid());
    const QString torrentPath = makeFixtureTorrent(tmp.path());
    const QString save = tmp.path() + "/dl";

    // Place the torrent's files at the save path with the ".!bt" suffix the app
    // gives in-progress files, so libtorrent has real files on disk to move when
    // the folder is renamed (same content as the fixture → byte sizes match).
    QDir().mkpath(save + "/bat_fixture/sub");
    auto put = [](const QString &p, int n){ QFile f(p); f.open(QIODevice::WriteOnly); f.write(QByteArray(n, 'x')); f.close(); };
    put(save + "/bat_fixture/a.txt.!bt", 100);
    put(save + "/bat_fixture/sub/b.txt.!bt", 200);

    SessionManager session;
    session.setAutoRecheck(false);   // skip recheck so the ".!bt" strip can't race the rename
    MetadataResolver resolver;
    QmlSessionBridge bridge(&session, &resolver);

    session.addTorrent(torrentPath, save);
    REQUIRE(pumpUntil([&] { return session.torrentCount() == 1; }));
    bridge.setSelectedRows({0});
    REQUIRE(bridge.hasSelection());
    REQUIRE(QFileInfo::exists(save + "/bat_fixture"));

    bridge.renameSelected("Renamed Collection");

    // Data ends up under the new folder and the empty old folder is pruned.
    REQUIRE(pumpUntil([&] {
        return QFileInfo::exists(save + "/Renamed Collection")
            && !QFileInfo::exists(save + "/bat_fixture");
    }, 15000));
    wipeBatState();
}

TEST_CASE("Session bridge: renaming a single-file torrent renames the file + the name", "[bridge][session][rename]")
{
    app();
    wipeBatState();
    QTemporaryDir tmp;
    REQUIRE(tmp.isValid());
    const QString torrentPath = makeSingleFileTorrent(tmp.path());
    QDir().mkpath(tmp.path() + "/dl");

    SessionManager session;
    MetadataResolver resolver;
    QmlSessionBridge bridge(&session, &resolver);

    session.addTorrent(torrentPath, tmp.path() + "/dl");
    REQUIRE(pumpUntil([&] { return session.torrentCount() == 1; }));
    bridge.setSelectedRows({0});
    REQUIRE(bridge.hasSelection());

    REQUIRE(bridge.selectedName() == "single_fixture.bin");
    bridge.renameSelected("renamed_single.bin");
    REQUIRE(bridge.selectedName() == "renamed_single.bin");

    REQUIRE(pumpUntil([&] {
        const QVariantList fl = bridge.selectedFiles();
        return fl.size() == 1
            && fl.value(0).toMap().value("path").toString().contains("renamed_single.bin");
    }));
    wipeBatState();
}

// ============================================================================
//  QmlSessionBridge — remove. Regression 1: delete-with-files only removed the
//  last-clicked torrent (m_selectedIndex) instead of the whole selection.
//  Regression 2: a multi-file torrent's folder was left behind on disk because
//  the top-level path was computed with '/' only (libtorrent uses '\' on
//  Windows), so files were trashed individually and the folder remained.
// ============================================================================
TEST_CASE("Session bridge: delete-with-files removes every selected torrent, not just the last", "[bridge][session][remove]")
{
    app();
    wipeBatState();
    QTemporaryDir tmp;
    REQUIRE(tmp.isValid());
    QDir().mkpath(tmp.path() + "/dl");

    SessionManager session;
    MetadataResolver resolver;
    QmlSessionBridge bridge(&session, &resolver);

    // Three distinct torrents; data lives in tmp/ (not the save path) so the
    // delete has nothing to trash on disk — this isolates the selection logic.
    for (int i = 0; i < 3; ++i)
        session.addTorrent(makeDistinctTorrent(tmp.path(), i), tmp.path() + "/dl");
    REQUIRE(pumpUntil([&] { return session.torrentCount() == 3; }));

    bridge.setSelectedRows({0, 1, 2});
    REQUIRE(bridge.hasSelection());

    bridge.removeSelectedWithFiles();
    REQUIRE(pumpUntil([&] { return session.torrentCount() == 0; }));
    wipeBatState();
}

#ifdef Q_OS_WIN
// Windows-only: the bug is the backslash separator, and the delete uses
// QFile::moveToTrash, which is reliable here but not in headless Linux CI.
TEST_CASE("Session bridge: deleting a folder torrent removes the whole folder, not just contents", "[bridge][session][remove]")
{
    app();
    wipeBatState();
    QTemporaryDir tmp;
    REQUIRE(tmp.isValid());
    const QString torrentPath = makeFixtureTorrent(tmp.path());
    const QString save = tmp.path() + "/dl";

    // Recreate the torrent's folder on disk with the ".!bt" names the app tracks
    // for in-progress files — the exact case where the buggy path trashed each
    // file and left the folder behind.
    QDir().mkpath(save + "/bat_fixture/sub");
    auto put = [](const QString &p, int n){ QFile f(p); f.open(QIODevice::WriteOnly); f.write(QByteArray(n, 'x')); f.close(); };
    put(save + "/bat_fixture/a.txt.!bt", 100);
    put(save + "/bat_fixture/sub/b.txt.!bt", 200);

    SessionManager session;
    session.setAutoRecheck(false);
    MetadataResolver resolver;
    QmlSessionBridge bridge(&session, &resolver);
    session.addTorrent(torrentPath, save);
    REQUIRE(pumpUntil([&] { return session.torrentCount() == 1; }));
    bridge.setSelectedRows({0});
    REQUIRE(bridge.hasSelection());
    REQUIRE(QFileInfo::exists(save + "/bat_fixture"));

    bridge.removeSelectedWithFiles();
    REQUIRE(pumpUntil([&] { return session.torrentCount() == 0; }));
    // The delete runs moveToTrash on a ~900ms timer; wait for the whole folder
    // (not just its files) to disappear from the save path.
    REQUIRE(pumpUntil([&] { return !QFileInfo::exists(save + "/bat_fixture"); }, 5000));
    wipeBatState();
}

// The active-download case: while files are open the first moveToTrash attempts
// fail (sharing violation), and the retry must finish the job once the handle
// is released. Regression: a single attempt left in-progress downloads on disk.
TEST_CASE("Session bridge: deleting a locked (downloading) folder retries until released", "[bridge][session][remove]")
{
    app();
    wipeBatState();
    QTemporaryDir tmp;
    REQUIRE(tmp.isValid());
    const QString torrentPath = makeFixtureTorrent(tmp.path());
    const QString save = tmp.path() + "/dl";
    QDir().mkpath(save + "/bat_fixture/sub");
    auto put = [](const QString &p, int n){ QFile f(p); f.open(QIODevice::WriteOnly); f.write(QByteArray(n, 'x')); f.close(); };
    put(save + "/bat_fixture/a.txt.!bt", 100);
    put(save + "/bat_fixture/sub/b.txt.!bt", 200);

    SessionManager session;
    session.setAutoRecheck(false);
    MetadataResolver resolver;
    QmlSessionBridge bridge(&session, &resolver);
    session.addTorrent(torrentPath, save);
    REQUIRE(pumpUntil([&] { return session.torrentCount() == 1; }));
    bridge.setSelectedRows({0});
    REQUIRE(bridge.hasSelection());

    // Hold a file open like an in-progress download would (Qt opens without
    // FILE_SHARE_DELETE), so moveToTrash hits a sharing violation at first.
    QFile lock(save + "/bat_fixture/a.txt.!bt");
    REQUIRE(lock.open(QIODevice::ReadOnly));
    QTimer::singleShot(1500, [&lock]{ lock.close(); });   // release mid-retry

    bridge.removeSelectedWithFiles();
    REQUIRE(pumpUntil([&] { return session.torrentCount() == 0; }));
    // Folder survives while locked, then the backoff retry clears it.
    REQUIRE(pumpUntil([&] { return !QFileInfo::exists(save + "/bat_fixture"); }, 12000));
    wipeBatState();
}
#endif

// ============================================================================
//  SessionManager — deleteTorrentOnAdd: remove the source .torrent after add.
// ============================================================================
TEST_CASE("Session: deleteTorrentOnAdd removes the source .torrent after adding", "[bridge][session][add]")
{
    app();
    wipeBatState();
    QTemporaryDir tmp;
    REQUIRE(tmp.isValid());
    const QString torrentPath = makeFixtureTorrent(tmp.path());
    QDir().mkpath(tmp.path() + "/dl");

    SessionManager session;
    session.setDeleteTorrentOnAdd(true);
    MetadataResolver resolver;
    QmlSessionBridge bridge(&session, &resolver);

    REQUIRE(QFileInfo::exists(torrentPath));
    session.addTorrent(torrentPath, tmp.path() + "/dl");
    REQUIRE(pumpUntil([&] { return session.torrentCount() == 1; }));
    REQUIRE(pumpUntil([&] { return !QFileInfo::exists(torrentPath); }));
    wipeBatState();
}

TEST_CASE("Session: the source .torrent is kept when deleteTorrentOnAdd is off", "[bridge][session][add]")
{
    app();
    wipeBatState();
    QTemporaryDir tmp;
    REQUIRE(tmp.isValid());
    const QString torrentPath = makeFixtureTorrent(tmp.path());
    QDir().mkpath(tmp.path() + "/dl");

    SessionManager session;
    session.setDeleteTorrentOnAdd(false);
    MetadataResolver resolver;
    QmlSessionBridge bridge(&session, &resolver);

    session.addTorrent(torrentPath, tmp.path() + "/dl");
    REQUIRE(pumpUntil([&] { return session.torrentCount() == 1; }));
    CHECK(QFileInfo::exists(torrentPath));   // left on disk
    wipeBatState();
}

TEST_CASE("Session: torrentMoveDir moves the source .torrent into the chosen folder", "[bridge][session][add]")
{
    app();
    wipeBatState();
    QTemporaryDir tmp;
    REQUIRE(tmp.isValid());
    const QString torrentPath = makeFixtureTorrent(tmp.path());   // tmp/sample.torrent
    const QString moveDir = tmp.path() + "/torrents";
    QDir().mkpath(tmp.path() + "/dl");

    SessionManager session;
    session.setTorrentMoveDir(moveDir);   // folder doesn't exist yet — created on demand
    MetadataResolver resolver;
    QmlSessionBridge bridge(&session, &resolver);

    REQUIRE(QFileInfo::exists(torrentPath));
    session.addTorrent(torrentPath, tmp.path() + "/dl");
    REQUIRE(pumpUntil([&] { return session.torrentCount() == 1; }));
    REQUIRE(pumpUntil([&] {
        return !QFileInfo::exists(torrentPath)                      // moved out of source
            && QFileInfo::exists(moveDir + "/sample.torrent");      // ...into the move folder
    }));
    wipeBatState();
}

TEST_CASE("Session: a move folder takes precedence over delete-on-add", "[bridge][session][add]")
{
    app();
    wipeBatState();
    QTemporaryDir tmp;
    REQUIRE(tmp.isValid());
    const QString torrentPath = makeFixtureTorrent(tmp.path());
    const QString moveDir = tmp.path() + "/torrents";
    QDir().mkpath(tmp.path() + "/dl");

    SessionManager session;
    session.setTorrentMoveDir(moveDir);
    session.setDeleteTorrentOnAdd(true);   // both on → move should win (file preserved)
    MetadataResolver resolver;
    QmlSessionBridge bridge(&session, &resolver);

    session.addTorrent(torrentPath, tmp.path() + "/dl");
    REQUIRE(pumpUntil([&] { return session.torrentCount() == 1; }));
    REQUIRE(pumpUntil([&] { return QFileInfo::exists(moveDir + "/sample.torrent"); }));
    wipeBatState();
}

// ============================================================================
//  SessionManager — speed/queue/network prefs persist across a "restart"
//  Regression: the QWidget→QML migration left these setters writing only to the
//  live libtorrent session (never QSettings) and the ctor never reloaded them,
//  so every limit reset to 0/default on relaunch ("settings don't save").
// ============================================================================
TEST_CASE("Session: speed/queue/network prefs survive a restart", "[bridge][session][persist]")
{
    app();
    QSettings("BATorrent", "BATorrent").clear();   // self-contained: don't inherit or leak state
    {
        SessionManager s;                       // user changes settings...
        s.setUploadLimit(123);
        s.setDownloadLimit(456);
        s.setMaxActiveDownloads(7);
        s.setSeedRatioLimit(2.5f);
        s.setMaxConnections(321);
        s.setDhtEnabled(false);
        s.setEncryptionMode(2);
        s.setPreallocate(true);
        s.setAutoRecheck(true);
        QSettings("BATorrent", "BATorrent").sync();   // flush before the "restart"
    }
    {
        SessionManager s2;                      // ...fresh instance = app relaunch
        // member-backed getters: deterministic right after the ctor's reload
        REQUIRE(s2.uploadLimit() == 123);
        REQUIRE(s2.downloadLimit() == 456);
        REQUIRE(s2.maxActiveDownloads() == 7);
        REQUIRE(s2.seedRatioLimit() == 2.5f);
        REQUIRE(s2.dhtEnabled() == false);
        REQUIRE(s2.encryptionMode() == 2);
        REQUIRE(s2.preallocate() == true);
        REQUIRE(s2.autoRecheck() == true);
    }
    // The keys that drive live libtorrent state are verified at the storage layer
    // (the getter reads the async session, which needn't have settled yet).
    QSettings st("BATorrent", "BATorrent");
    REQUIRE(st.value("maxConnections").toInt() == 321);
    REQUIRE(st.value("uploadLimit").toInt() == 123);
    st.clear();   // leave the store clean for sibling tests / the next run
}

// ============================================================================
//  QmlSettingsBridge — UI bool toggles coerce to a real bool on read.
//  Regression: on the Windows registry a bool round-trips as an int (DWORD), so
//  QML's `settings.get(key) !== false` saw `0 !== false` → true and the splash /
//  close-to-tray toggles ignored being switched off.
// ============================================================================
TEST_CASE("Settings bridge: UI bool toggles read back as real bool", "[bridge][settings][persist]")
{
    app();
    SessionManager s;
    QmlSettingsBridge sb(&s);

    // Mimic the Windows DWORD readback: store the toggle as an int, not a bool.
    QSettings().setValue(QStringLiteral("showSplash"), 0);
    QSettings().sync();

    const QVariant v = sb.get(QStringLiteral("showSplash"));
    REQUIRE(v.typeId() == QMetaType::Bool);          // coerced — not the raw int 0
    REQUIRE(v.toBool() == false);
    REQUIRE_FALSE(v.toBool() != false);              // the exact compare QML relies on

    sb.set(QStringLiteral("showSplash"), true);
    REQUIRE(sb.get(QStringLiteral("showSplash")).toBool() == true);

    // An unset toggle stays invalid so QML's own `on:` default still applies.
    QSettings().remove(QStringLiteral("randomPort"));
    QSettings().sync();
    REQUIRE_FALSE(sb.get(QStringLiteral("randomPort")).isValid());
}
