# Fork backlog

Work queued for the coex177 fork, newest intent first. Upstream-bound items
are tracked separately in the PR branches.

## Next up

- [x] **Scrollbar visibility setting** — let the user choose `AlwaysOn` vs
      `AsNeeded` for the list/grid scrollbars, instead of hard-coding
      `AsNeeded`. Applies to `LibraryView` (grid + list) and the detail panes
      (Files/Peers/Trackers/Pieces). Shipped in 4.7.0a-rc3.

## Shipped in 4.7.0b-rc3

- [x] **Star torrents to pin the top-bar chip** — starred torrents drive the
      chip rotation. Backed by `session.starredTransfers` (walks all torrents,
      since a finished-in-an-earlier-run torrent isn't in activeDownloads or
      seedingTransfers).
- [x] **Disk gauge selection + cycle speeds** — pick monitored drives
      (one/several/all) and set chip/disk cycle intervals. Shared `DiskMonitor`
      widget so the top bar and classic rail use one filter.
- [x] **Resume-scan UI stall fix** — `resumeItems` no longer scans every
      torrent's files each 8s (upstream bug; candidate for an upstream PR).
- [x] **On-disk rename failures surfaced** — `file_rename_failed_alert` handled;
      toast with the real reason instead of a silent display/disk divergence.

## Porting to 4.7 (branch `merge/upstream-4.7`)

Re-applying fork features on top of the upstream v4.7.0 merge.

- [x] Torrent rename (file/folder + display name, F2)
- [x] "Added on" column, sortable
- [x] Periodic resume save (5 min)
- [x] Vertical scrollbars (grid, list, detail panes)
- [x] Delete key opens the Remove dialog
- [x] File double-click opens with the OS default app
- [x] Sort column/direction + detail tab persistence
- [x] Pinned column header (also fixes header sort clicks being eaten
      by the selection overlay)
- [x] Compact view — delivered as a **dense rows** toggle. Upstream's classic
      row is already cover-less, so only the row height (56 -> 40) was missing;
      a third toggle segment would have been near-identical to Classic.
- [x] Rename dialog: separate file-extension field
- [x] Settings: `torrentMoveDir` ("move added .torrent files") and
      `deleteTorrentOnAdd`

## Dropped (superseded upstream)

- Atomic `.resume` write — upstream fixed it independently with `QSaveFile`.
- Tray right-click menu — upstream uses a painted `TrayPopupWindow` instead.
- Remove-while-locked retries — upstream's version is further along
  (`permanent` flag, `pendingDeleteTargets` across restarts, backoff).
- Dead-QML removal (`TrayPopupWindow`, `ToastHost`) — both are live upstream.
