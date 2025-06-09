# Windows Quick Setup Script
param([string] = "setup")
function Write-Success { param() Write-Host "✅ " -ForegroundColor Green }
function Write-Error { param() Write-Host " " -ForegroundColor Red }
function Write-Info { param() Write-Host " " -ForegroundColor Cyan }

# Auto-detect dan install C++ compiler
function Setup-Compiler {
    if (Get-Command "g++" -ErrorAction SilentlyContinue) {
        Write-Success "C++ compiler found!"
        return True
    }
    
    Write-Info "Installing C++ compiler..."
    if (Get-Command "winget" -ErrorAction SilentlyContinue) {
        winget install -e --id GnuWin32.Make
        winget install -e --id mingw-w64
    } else {
        Write-Info "Please install MinGW manually: https://www.mingw-w64.org/"
        Write-Info "Or run: choco install mingw (if you have chocolatey)"
    }
}

# Auto setup everything
function Auto-Setup {
    Write-Info " Setting up Method B Network Analyzer..."
    
    # Create directories
    "data\raw","data\processed","data\results","docs\visualizations" | ForEach-Object { 
        New-Item -ItemType Directory -Force -Path  | Out-Null 
    }
    Write-Success "Directories created!"
    
    # Setup compiler
    Setup-Compiler
    
    # Compile programs
    if (Get-Command "g++" -ErrorAction SilentlyContinue) {
        Write-Info "Compiling programs..."
        & g++ -std=c++11 -O2 -o enhanced_analyzer.exe src\main.cpp src\network_analyzer.cpp 2>
        & g++ -std=c++11 -O2 -o data_visualizer.exe data_visualizer.cpp 2>  
        & g++ -std=c++11 -O2 -o simple_visualizer.exe simple_visualizer.cpp 2>
        
        if (Test-Path "enhanced_analyzer.exe") { Write-Success " All programs compiled!" }
        else { Write-Error "Compilation failed - check compiler installation" }
    }
    
    Write-Success " Setup completed! Run: .\quick-setup.ps1 demo"
}

switch () {
    "setup" { Auto-Setup }
    "demo" { 
        if (Test-Path "enhanced_analyzer.exe") {
            Write-Info " Running demo..."
            .\enhanced_analyzer.exe
        } else {
            Write-Error "Run setup first: .\quick-setup.ps1 setup"
        }
    }
    "viz" {
        if (Test-Path "simple_visualizer.exe") {
            .\simple_visualizer.exe
        } else {
            Write-Error "Run setup first: .\quick-setup.ps1 setup"
        }
    }
    default { Write-Info "Usage: .\quick-setup.ps1 [setup|demo|viz]" }
}
