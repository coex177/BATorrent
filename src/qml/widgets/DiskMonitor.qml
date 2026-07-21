// SPDX-License-Identifier: MIT
// Copyright (c) 2024-2026 Mateus Cruz
// See LICENSE file for details

// Non-visual state of the disk gauge, shared by the top bar (rotates one
// volume at a time) and the nav rail (lists them all). Filters the session's
// volume list down to the ones the user chose to monitor, empty = every one.
import QtQuick

QtObject {
    id: dm
    property bool active: true            // host visibility gate for the rotation

    readonly property var allVolumes: (typeof session !== "undefined") ? session.diskVolumes : []
    property var pickedSet: ({})          // volume name -> true; empty means "all"
    property int cycleMs: 5000

    function reloadPrefs() {
        if (typeof settings === "undefined") return
        var m = {}
        var parts = String(settings.get("monitoredDisks") || "").split("|")
        for (var i = 0; i < parts.length; ++i) if (parts[i].length > 0) m[parts[i]] = true
        dm.pickedSet = m
        var s = Number(settings.get("diskCycleSec"))
        dm.cycleMs = (s >= 1 && s <= 120) ? s * 1000 : 5000
    }
    Component.onCompleted: reloadPrefs()
    readonly property var prefWatch: Connections {
        target: typeof settings !== "undefined" ? settings : null
        function onChanged() { dm.reloadPrefs() }
    }

    // A picked volume that's since been unplugged just drops out; if every pick
    // is gone we fall back to all, so the gauge never goes blank.
    readonly property var volumes: {
        if (Object.keys(pickedSet).length === 0) return allVolumes
        var out = []
        for (var i = 0; i < allVolumes.length; ++i)
            if (pickedSet[allVolumes[i].name] === true) out.push(allVolumes[i])
        return out.length > 0 ? out : allVolumes
    }

    property int idx: 0
    readonly property var shown: volumes.length > 0
        ? volumes[Math.min(idx, volumes.length - 1)] : null

    onVolumesChanged: if (idx >= volumes.length) idx = 0

    readonly property Timer cycler: Timer {
        interval: dm.cycleMs
        running: dm.active && dm.volumes.length > 1
        repeat: true
        onTriggered: dm.idx = (dm.idx + 1) % dm.volumes.length
    }
}
