@echo off
echo 🚀 Method B Network Analyzer - Auto Installer
echo Calvin Wirathama Katoroy - NPM: 2306242395
echo.

:: Check if PowerShell is available
powershell -Command "Write-Host 'PowerShell available!'" 2>nul
if %errorlevel% neq 0 (
    echo ❌ PowerShell required!
    pause
    exit /b 1
)

:: Run PowerShell setup
powershell -ExecutionPolicy Bypass -File "quick-setup.ps1" setup
pause