// SPDX-License-Identifier: MIT
// Copyright (c) 2024-2026 Mateus Cruz
// See LICENSE file for details

// Reusable single-field prompt (rate limits, category, tag, tracker, …).
// Open via openWith(title, label, value, placeholder, callback); the trimmed
// text is passed to the callback when the user confirms.
import QtQuick
import QtQuick.Layouts
import "theme"
import "widgets"

BatDialog {
    id: dlg
    cardW: 440
    cardH: 220
    okText: (i18n.language, i18n.t("btn_ok"))
    // Enter is handled by the field below; turn off the base dialog's own
    // Return shortcut so a focused field doesn't swallow it (and we never
    // double-accept).
    acceptOnReturn: false

    property string promptLabel: ""
    property string promptPlaceholder: ""
    property var onAccept: null
    // Only set for things that actually have an extension (files, single-file
    // torrents); folder torrents pass false so the dots in a release name stay
    // in the name field.
    property bool splitExt: false

    onAccepted: if (onAccept) onAccept(dlg.finalText())

    function finalText() {
        var base = field.text.trim()
        if (!dlg.splitExt) return base
        var e = extField.text.trim().replace(/^\.+/, "")
        return e.length > 0 ? base + "." + e : base
    }

    function openWith(t, label, value, placeholder, cb, splitExtension) {
        dlg.title = t
        dlg.promptLabel = label || ""
        dlg.promptPlaceholder = placeholder || ""
        dlg.splitExt = splitExtension === true
        var v = value || ""
        var i = dlg.splitExt ? v.lastIndexOf(".") : -1   // i > 0 keeps ".gitignore" whole
        field.text = i > 0 ? v.slice(0, i) : v
        extField.text = i > 0 ? v.slice(i + 1) : ""
        dlg.onAccept = cb
        dlg.open()
        // defer until the dialog is shown so the editor can take focus
        Qt.callLater(field.focusText)
    }

    ColumnLayout {
        Layout.fillWidth: true
        spacing: 8

        Text {
            text: dlg.promptLabel
            visible: dlg.promptLabel.length > 0
            color: Theme.t3
            font.pixelSize: 11
            font.weight: Font.DemiBold
            font.family: Theme.fontSans
            Layout.fillWidth: true
            wrapMode: Text.WordWrap
        }

        RowLayout {
            Layout.fillWidth: true
            spacing: 6

            TFld {
                id: field
                Layout.fillWidth: true
                placeholder: dlg.promptPlaceholder
                onAccepted: { dlg.accepted(); dlg.close() }
            }
            Text {
                visible: dlg.splitExt
                text: "."
                color: Theme.t3
                font.pixelSize: 13
                font.family: Theme.fontSans
                Layout.alignment: Qt.AlignVCenter
            }
            TFld {
                id: extField
                visible: dlg.splitExt
                Layout.preferredWidth: 84
                onAccepted: { dlg.accepted(); dlg.close() }
            }
        }
    }
}
