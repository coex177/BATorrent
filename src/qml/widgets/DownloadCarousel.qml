// SPDX-License-Identifier: MIT
// Copyright (c) 2024-2026 Mateus Cruz
// See LICENSE file for details

// Non-visual state of the contextual download carousel, shared by the nav
// rail (classic layout) and the top-bar chip: off the Downloads page → live
// downloads (fallback: seeding), ON Downloads → continue/resume items.
import QtQuick

QtObject {
    id: car
    property int currentPage: 0
    property bool hovered: false
    property bool active: true            // host visibility gate for the cycle timer

    readonly property var downloadList: (typeof session !== "undefined") ? session.activeDownloads : []
    readonly property var seedingList: (typeof session !== "undefined") ? session.seedingTransfers : []
    readonly property var resumeList: (typeof session !== "undefined") ? session.resumeItems : []
    // ON Downloads prefer continue/resume items (the downloads are already on
    // screen); everywhere — including when there's nothing to resume — fall
    // back to live downloads, then seeding, so the slot is never empty while
    // anything is transferring.
    readonly property bool slotResume: currentPage === 0 && resumeList.length > 0
    readonly property bool slotSeed: !slotResume && downloadList.length === 0 && seedingList.length > 0

    // Starred torrents win outright: if the user picked any, the chip shows only
    // those, downloading or not. Nothing starred → the contextual logic above.
    readonly property var starredList: (typeof session !== "undefined") ? session.starredTransfers : []

    property int cycleMs: 5000
    function reloadPrefs() {
        if (typeof settings === "undefined") return
        var s = Number(settings.get("chipCycleSec"))
        car.cycleMs = (s >= 1 && s <= 120) ? s * 1000 : 5000
    }
    Component.onCompleted: reloadPrefs()
    readonly property var prefWatch: Connections {
        target: typeof settings !== "undefined" ? settings : null
        function onChanged() { car.reloadPrefs() }
    }

    readonly property var dlList: starredList.length > 0 ? starredList
                                : (slotResume ? resumeList
                                : (downloadList.length > 0 ? downloadList : seedingList))
    property int dlIndex: 0
    property int dlShown: 0
    readonly property var dlItem: (dlList.length > dlShown && dlShown >= 0) ? dlList[dlShown]
                                  : (dlList.length > 0 ? dlList[0] : null)

    onSlotResumeChanged: { dlIndex = 0; dlShown = 0 }
    onDlListChanged: if (dlShown >= dlList.length) dlShown = Math.max(0, dlList.length - 1)

    function next() { if (dlList.length > 0) dlIndex = (dlIndex + 1) % dlList.length }
    function prev() { if (dlList.length > 0) dlIndex = (dlIndex - 1 + dlList.length) % dlList.length }

    readonly property Timer cycler: Timer {
        interval: car.cycleMs
        running: car.active && car.dlList.length > 1 && !car.hovered
        repeat: true
        onTriggered: car.next()
    }
}
