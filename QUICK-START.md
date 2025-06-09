# 🎯 INSTANT SETUP (30 seconds)

## Option 1: One-Command (Copy-Paste)

**Windows:** 

```powershell
# One-liner setup (copy-paste dan enter):
Set-ExecutionPolicy -ExecutionPolicy RemoteSigned -Scope CurrentUser -Force; if (!(Test-Path "quick-setup.ps1")) { @"
# Windows Quick Setup Script
param([string]$Action = "setup")
function Write-Success { param($msg) Write-Host "✅ $msg" -ForegroundColor Green }
function Write-Error { param($msg) Write-Host "❌ $msg" -ForegroundColor Red }
function Write-Info { param($msg) Write-Host "💡 $msg" -ForegroundColor Cyan }

# Auto-detect dan install C++ compiler
function Setup-Compiler {
    if (Get-Command "g++" -ErrorAction SilentlyContinue) {
        Write-Success "C++ compiler found!"
        return $true
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
    Write-Info "🚀 Setting up Method B Network Analyzer..."
  
    # Create directories
    "data\raw","data\processed","data\results","docs\visualizations" | ForEach-Object { 
        New-Item -ItemType Directory -Force -Path $_ | Out-Null 
    }
    Write-Success "Directories created!"
  
    # Setup compiler
    Setup-Compiler
  
    # Compile programs
    if (Get-Command "g++" -ErrorAction SilentlyContinue) {
        Write-Info "Compiling programs..."
        & g++ -std=c++11 -O2 -o enhanced_analyzer.exe src\main.cpp src\network_analyzer.cpp 2>$null
        & g++ -std=c++11 -O2 -o data_visualizer.exe data_visualizer.cpp 2>$null  
        & g++ -std=c++11 -O2 -o simple_visualizer.exe simple_visualizer.cpp 2>$null
      
        if (Test-Path "enhanced_analyzer.exe") { Write-Success "✅ All programs compiled!" }
        else { Write-Error "Compilation failed - check compiler installation" }
    }
  
    Write-Success "🎉 Setup completed! Run: .\quick-setup.ps1 demo"
}

switch ($Action) {
    "setup" { Auto-Setup }
    "demo" { 
        if (Test-Path "enhanced_analyzer.exe") {
            Write-Info "🎬 Running demo..."
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
"@ | Out-File -FilePath "quick-setup.ps1" -Encoding UTF8 }; .\quick-setup.ps1 setup
```

**Linux/macOS:** 

```bash
# One-liner setup (copy-paste dan enter):
curl -fsSL https://raw.githubusercontent.com/user/repo/main/quick-setup.sh || { cat > quick-setup.sh << 'EOF'
#!/bin/bash
# Linux/macOS Quick Setup Script

GREEN='\033[0;32m'
RED='\033[0;31m'
CYAN='\033[0;36m'
NC='\033[0m'

success() { echo -e "${GREEN}✅ $1${NC}"; }
error() { echo -e "${RED}❌ $1${NC}"; }
info() { echo -e "${CYAN}💡 $1${NC}"; }

# Auto-detect dan install dependencies
setup_dependencies() {
    if command -v g++ &> /dev/null; then
        success "C++ compiler found!"
    else
        info "Installing C++ compiler..."
        if [[ "$OSTYPE" == "linux-gnu"* ]]; then
            sudo apt-get update && sudo apt-get install -y build-essential
        elif [[ "$OSTYPE" == "darwin"* ]]; then
            xcode-select --install
        fi
    fi
  
    # Optional: Install make if not available
    if ! command -v make &> /dev/null; then
        info "Installing make..."
        if [[ "$OSTYPE" == "linux-gnu"* ]]; then
            sudo apt-get install -y make
        elif [[ "$OSTYPE" == "darwin"* ]]; then
            brew install make
        fi
    fi
}

# Auto setup everything
auto_setup() {
    info "🚀 Setting up Method B Network Analyzer..."
  
    # Create directories
    mkdir -p data/{raw,processed,results} docs/visualizations
    success "Directories created!"
  
    # Setup dependencies
    setup_dependencies
  
    # Compile programs
    if command -v g++ &> /dev/null; then
        info "Compiling programs..."
        g++ -std=c++11 -O2 -o enhanced_analyzer src/main.cpp src/network_analyzer.cpp 2>/dev/null
        g++ -std=c++11 -O2 -o data_visualizer data_visualizer.cpp 2>/dev/null
        g++ -std=c++11 -O2 -o simple_visualizer simple_visualizer.cpp 2>/dev/null
      
        if [[ -f "enhanced_analyzer" ]]; then
            success "✅ All programs compiled!"
            chmod +x enhanced_analyzer data_visualizer simple_visualizer
        else
            error "Compilation failed - check source files"
        fi
    fi
  
    success "🎉 Setup completed! Run: ./quick-setup.sh demo"
}

case ${1:-setup} in
    setup) auto_setup ;;
    demo) 
        if [[ -f "enhanced_analyzer" ]]; then
            info "🎬 Running demo..."
            ./enhanced_analyzer
        else
            error "Run setup first: ./quick-setup.sh setup"
        fi
        ;;
    viz)
        if [[ -f "simple_visualizer" ]]; then
            ./simple_visualizer
        else
            error "Run setup first: ./quick-setup.sh setup"
        fi
        ;;
    *) info "Usage: ./quick-setup.sh [setup|demo|viz]" ;;
esac
EOF
chmod +x quick-setup.sh; }; ./quick-setup.sh setup
```

## Option 2: Double-Click

**Windows:** Double-click `install.bat`
**Linux/macOS:** Double-click `install.sh`

## Option 3: Node.js Style

```bash
npm install && npm run demo
```
