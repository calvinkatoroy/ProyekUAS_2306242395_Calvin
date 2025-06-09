// setup.js - Universal cross-platform setup
const { execSync } = require('child_process');
const fs = require('fs');
const path = require('path');

const isWindows = process.platform === 'win32';
const compiler = isWindows ? 'g++.exe' : 'g++';

// Auto-detect and setup
function autoSetup() {
    console.log('🚀 Auto-setting up Method B Network Analyzer...');
    
    // Create directories
    ['data/raw', 'data/processed', 'data/results', 'docs/visualizations'].forEach(dir => {
        fs.mkdirSync(dir, { recursive: true });
    });
    
    // Check compiler
    try {
        execSync(`${compiler} --version`, { stdio: 'ignore' });
        console.log('✅ C++ compiler found!');
        
        // Compile programs
        const ext = isWindows ? '.exe' : '';
        execSync(`${compiler} -std=c++11 -O2 -o enhanced_analyzer${ext} src/main.cpp src/network_analyzer.cpp`);
        execSync(`${compiler} -std=c++11 -O2 -o data_visualizer${ext} data_visualizer.cpp`);
        execSync(`${compiler} -std=c++11 -O2 -o simple_visualizer${ext} simple_visualizer.cpp`);
        
        console.log('✅ All programs compiled!');
        console.log('🎉 Setup completed! Run: npm start');
        
    } catch (error) {
        console.log('❌ C++ compiler not found!');
        console.log('💡 Install: MinGW (Windows) or build-essential (Linux)');
    }
}

autoSetup();