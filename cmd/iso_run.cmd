@echo off

set ISO_IMG="C:\Longman Dictionary of Contemporary English 2003.iso"
set RUN_DIR="%ProgramFiles%\Longman\LDOCE\"
REM Here no quotations needed because "start" would looks on it as title
set RUN_EXE=ldoce.exe

if not exist "%ProgramFiles%\WinCDEmu\vmnt.exe" (
    echo WinCDEmu not installed!
    pause
    exit
)

if not exist %ISO_IMG% (
    echo Cannot find ISO Image %ISO_IMG%!
    pause
    exit
)

set PATH=%PATH%;%ProgramFiles%\WinCDEmu\

if not exist V: vmnt %ISO_IMG%

if not exist %RUN_DIR%%RUN_EXE% (
    echo Cannot find executable file %RUN_DIR%%RUN_EXE%!
    pause
    exit
)

start /d%RUN_DIR% %RUN_EXE%

echo on
