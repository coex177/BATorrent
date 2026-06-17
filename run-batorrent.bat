@echo off
REM Launch the locally-built BATorrent (MSYS2/mingw64 build).
REM Qt + libtorrent DLLs and Qt plugins are resolved from the mingw64 prefix.
set "PATH=C:\msys64\mingw64\bin;%PATH%"
start "" "%~dp0build\BATorrent.exe"
