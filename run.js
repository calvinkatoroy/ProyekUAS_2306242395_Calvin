// run.js - Cross-platform program runner
const { spawn } = require('child_process');
const path = require('path');

const isWindows = process.platform === 'win32';
const executable = isWindows ? 'enhanced_analyzer.exe' : './enhanced_analyzer';

if (require('fs').existsSync(executable)) {
    console.log('🎬 Running Method B Network Analyzer...');
    const child = spawn(executable, [], { stdio: 'inherit' });
    child.on('close', (code) => {
        if (code === 0) {
            console.log('✅ Analysis completed!');
            console.log('💡 Run visualizations: npm run viz');
        }
    });
} else {
    console.log('❌ Program not found! Run: npm run setup');
}