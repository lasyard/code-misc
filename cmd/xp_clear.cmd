@echo off

REM Delete useless files in WinXP

echo Clear Prefetch
for /d %%d in ("%windir%\Prefetch\*") do rd /s /q "%%d"
del /f /q "%windir%\Prefetch\*"

echo Clear system temporary files
for /d %%d in ("%windir%\Temp\*") do rd /s /q "%%d"
del /f /q "%windir%\Temp\*"

echo Clear recent files
del /f /q "%userprofile%\Recent\*"

echo Clear nethood
for /d %%d in ("%userprofile%\NetHood\*") do rd /s /q "%%d"

echo Clear user temporary files
for /d %%d in ("%userprofile%\Local Settings\Temp\*") do rd /s /q "%%d"
del /f /q "%userprofile%\Local Settings\Temp\*"

echo Clear done.

pause
