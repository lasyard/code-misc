@echo off

if not exist "%ProgramFiles%\7-Zip\7z.exe" (
    echo 7Zip not installed!
    pause
    exit
)

set PATH=%PATH%;%ProgramFiles%\7-Zip\

for %%f in (%CD%) do set ZipName=%%~nf.7z

setlocal enabledelayedexpansion

for /F "delims=<> tokens=1,2" %%f in (FileList.txt) do (
    if "%%g"=="" (if not "%%f"=="" (
        if not exist "%%f" (
            echo %%f not exist!
        ) else (
            7z a "!ZipName!" %%f >NUL
            if not errorlevel 0 (
                echo Error occurred when 7z %%f.
            ) else (
                echo 7z %%f OK.
            )
        )
    )) else (
        if /i %%f==ZIP (
            set ZipName=%%g.zip
        ) else (if /i %%f==7Z (
            set ZipName=%%g.7z
        ))
        echo.
        echo Zip to !ZipName!.
        echo.
    )
)

setlocal disabledelayedexpansion

echo Done!
pause
echo on
