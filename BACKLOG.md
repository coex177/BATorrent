# Fork backlog

Work queued for the coex177 fork, newest intent first. Upstream-bound items
are tracked separately in the PR branches.

## Next up

- [x] **Scrollbar visibility setting** — let the user choose `AlwaysOn` vs
      `AsNeeded` for the list/grid scrollbars, instead of hard-coding
      `AsNeeded`. Applies to `LibraryView` (grid + list) and the detail panes
      (Files/Peers/Trackers/Pieces).

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
