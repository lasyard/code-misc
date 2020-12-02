@echo off

REM delete useless files for VC6 and VC2005

if "%1"=="" (
    echo Please input the path you want to clear.
    goto end
)

for /R %1 %%d in (.) do (
    del /a %%d\*.ncb
    REM Sometimes this file contain useful infomation, should not be deleted
    del /a %%d\*.opt
    del /a %%d\*.plg
    del /a %%d\*.aps
    REM These files only exist in VC2005 project
    del /a %%d\*.suo
    del /a %%d\*.vcproj.*.*.user
    REM The output directory
    rd /s /q %%d\Debug
    rd /s /q %%d\Release
)
echo clear done.

:end
echo on
