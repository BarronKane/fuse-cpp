@echo off
setlocal enableextensions
pushd "%~dp0"

CALL :GETPARENT PARENT
IF /I "%PARENT%" == "powershell" goto :ISPOWERSHELL
IF /I "%PARENT%" == "pwsh" goto :ISPOWERSHELL

call env\Scripts\activate.bat
if ERRORLEVEL 1 goto error 

goto :build 

:build 

md build
pushd build
conan install .. --build=missing -s build_type=Debug
cmake .. -G "Visual Studio 17 2022"
cmake --build .
popd

goto :EOF 

:ISPOWERSHELL 

echo POWERSHELL DETECTED,
echo you may have to run 'env/Scripts/Activate.ps1' manually.
REM $PSScriptRoot\env\Scripts\Activate.ps1

goto :build 

:error 
echo Python environment not setup, see README.md
pause
goto :EOF

:GETPARENT
SET "PSCMD=$ppid=$pid;while($i++ -lt 3 -and ($ppid=(Get-CimInstance Win32_Process -Filter ('ProcessID='+$ppid)).ParentProcessID)) {}; (Get-Process -EA Ignore -ID $ppid).Name"
for /f "tokens=*" %%i in ('powershell -noprofile -command "%PSCMD%"') do SET %1=%%i
goto :EOF