@echo off

if not exist "%ProgramFiles%\Monkey's Audio\MAC.exe" (
    echo Monkey's Audio not installed!
    echo Download it from http://www.monkeysaudio.com/
    pause
    exit
)

if not exist "%ProgramFiles%\FLAC\flac.exe" (
    echo FLAC not installed!
    echo Download it from http://flac.sourceforge.net/
    pause
    exit
)

set PATH=%PATH%;%ProgramFiles%\Monkey's Audio\;%ProgramFiles%\FLAC\

for %%f in (*.ape) do (
    MAC %%f %%~nf.wav -d 2>NUL
    flac -8 %%~nf.wav -o %%~nf.flac -f 2>NUL
    if not errorlevel 0 (
        echo Error occurred when convert %%f!
    ) else (
        echo Convert %%f OK!
    )
    del %%~nf.wav
)

echo Done!
pause
echo on
