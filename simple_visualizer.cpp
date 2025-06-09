// simple_visualizer.cpp
// Calvin Wirathama Katoroy - NPM: 2306242395
// Simple ASCII Visualization - No External Dependencies

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <cmath>

class SimpleVisualizer {
private:
    std::vector<double> hours;
    std::vector<double> bandwidth;
    std::vector<double> gradient;
    std::vector<double> rk4_prediction;
    
public:
    bool loadData(const std::string& filename = "data/results/enhanced_analysis_output.csv") {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cout << "❌ Error: Cannot open " << filename << std::endl;
            return false;
        }
        
        std::string line;
        std::getline(file, line); // Skip header
        
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string item;
            
            double h, b, g, c, r;
            std::getline(ss, item, ','); h = std::stod(item);
            std::getline(ss, item, ','); b = std::stod(item);
            std::getline(ss, item, ','); g = std::stod(item);
            std::getline(ss, item, ','); c = std::stod(item);
            std::getline(ss, item, ','); r = std::stod(item);
            
            hours.push_back(h);
            bandwidth.push_back(b);
            gradient.push_back(g);
            rk4_prediction.push_back(r);
        }
        
        file.close();
        std::cout << "✅ Data loaded: " << hours.size() << " records" << std::endl;
        return true;
    }
    
    void printBandwidthChart() {
        std::cout << "\n📊 BANDWIDTH CHART (24 HOURS)" << std::endl;
        std::cout << "Calvin Wirathama Katoroy - NPM: 2306242395" << std::endl;
        std::cout << std::string(70, '=') << std::endl;
        
        double max_bw = *std::max_element(bandwidth.begin(), bandwidth.end());
        double min_bw = *std::min_element(bandwidth.begin(), bandwidth.end());
        
        std::cout << "Scale: 0 Mbps" << std::string(35, ' ') << std::fixed << std::setprecision(2) << max_bw << " Mbps" << std::endl;
        std::cout << "       |" << std::string(49, '-') << "|" << std::endl;
        
        for (size_t i = 0; i < hours.size(); i++) {
            int bar_length = static_cast<int>((bandwidth[i] / max_bw) * 49);
            std::string bar(bar_length, '█');
            
            // Check if this is a peak (simplified)
            bool is_peak = false;
            if (i > 0 && i < bandwidth.size()-1) {
                is_peak = (bandwidth[i] > bandwidth[i-1] && bandwidth[i] > bandwidth[i+1] && 
                          bandwidth[i] > (max_bw * 0.7));
            }
            
            std::cout << std::setw(2) << static_cast<int>(hours[i]) << ":00 |" 
                      << std::setw(49) << std::left << bar << "|" 
                      << std::setw(6) << std::right << std::fixed << std::setprecision(2) << bandwidth[i];
            
            if (is_peak) std::cout << " ← PEAK";
            std::cout << std::endl;
        }
        
        std::cout << "       |" << std::string(49, '-') << "|" << std::endl;
    }
    
    void printGradientAnalysis() {
        std::cout << "\n📈 GRADIENT ANALYSIS (Rate of Change)" << std::endl;
        std::cout << std::string(60, '=') << std::endl;
        
        double max_grad = *std::max_element(gradient.begin(), gradient.end());
        double min_grad = *std::min_element(gradient.begin(), gradient.end());
        double range = std::max(std::abs(max_grad), std::abs(min_grad));
        
        std::cout << "Hour | Gradient  | Visualization" << std::endl;
        std::cout << "-----|-----------|" << std::string(40, '-') << std::endl;
        
        for (size_t i = 0; i < hours.size(); i++) {
            int center = 20;
            int pos = center + static_cast<int>((gradient[i] / range) * 15);
            pos = std::max(0, std::min(39, pos));
            
            std::string viz(40, ' ');
            viz[center] = '|';
            
            if (gradient[i] > 0.05) {
                for (int j = center; j <= pos; j++) viz[j] = '>';
                viz += " ↗ Increasing";
            } else if (gradient[i] < -0.05) {
                for (int j = pos; j <= center; j++) viz[j] = '<';
                viz += " ↘ Decreasing";
            } else {
                viz[center] = '•';
                viz += " → Stable";
            }
            
            std::cout << std::setw(2) << static_cast<int>(hours[i]) << ":00|" 
                      << std::setw(10) << std::fixed << std::setprecision(3) << gradient[i] << "|"
                      << viz.substr(0, 40) << std::endl;
        }
    }
    
    void printRK4Comparison() {
        std::cout << "\n🚀 RK4 PREDICTION vs HISTORICAL" << std::endl;
        std::cout << std::string(80, '=') << std::endl;
        
        double max_val = std::max(*std::max_element(bandwidth.begin(), bandwidth.end()),
                                 *std::max_element(rk4_prediction.begin(), rk4_prediction.end()));
        
        std::cout << "Hour | Historical | Prediction | Comparison Chart" << std::endl;
        std::cout << "-----|------------|------------|" << std::string(40, '-') << std::endl;
        
        for (size_t i = 0; i < hours.size(); i++) {
            int hist_len = static_cast<int>((bandwidth[i] / max_val) * 20);
            int pred_len = static_cast<int>((rk4_prediction[i] / max_val) * 20);
            
            std::string hist_bar(hist_len, '█');
            std::string pred_bar(pred_len, '▓');
            
            std::cout << std::setw(2) << static_cast<int>(hours[i]) << ":00|" 
                      << std::setw(11) << std::fixed << std::setprecision(2) << bandwidth[i] << "|"
                      << std::setw(11) << rk4_prediction[i] << "|"
                      << "H:" << std::setw(20) << std::left << hist_bar << std::endl;
            
            std::cout << "     |            |            |P:" 
                      << std::setw(20) << std::left << pred_bar << std::endl;
        }
        
        std::cout << "\nLegend: H=Historical █, P=Predicted ▓" << std::endl;
    }
    
    void printStatisticsSummary() {
        std::cout << "\n📊 METHOD B STATISTICS SUMMARY" << std::endl;
        std::cout << "Calvin Wirathama Katoroy - NPM: 2306242395" << std::endl;
        std::cout << std::string(50, '=') << std::endl;
        
        // Calculate statistics
        double avg_bw = 0, volatility = 0;
        for (size_t i = 0; i < bandwidth.size(); i++) {
            avg_bw += bandwidth[i];
            volatility += gradient[i] * gradient[i];
        }
        avg_bw /= bandwidth.size();
        volatility = std::sqrt(volatility / bandwidth.size());
        
        double max_bw = *std::max_element(bandwidth.begin(), bandwidth.end());
        double min_bw = *std::min_element(bandwidth.begin(), bandwidth.end());
        double max_grad = *std::max_element(gradient.begin(), gradient.end());
        double min_grad = *std::min_element(gradient.begin(), gradient.end());
        
        // Count peaks (simplified)
        int peak_count = 0;
        for (size_t i = 1; i < bandwidth.size()-1; i++) {
            if (bandwidth[i] > bandwidth[i-1] && bandwidth[i] > bandwidth[i+1] && 
                bandwidth[i] > avg_bw * 1.2) {
                peak_count++;
            }
        }
        
        std::cout << "🔹 Total Data Points: " << bandwidth.size() << " hours" << std::endl;
        std::cout << "🔹 Average Bandwidth: " << std::fixed << std::setprecision(3) << avg_bw << " Mbps" << std::endl;
        std::cout << "🔹 Peak Bandwidth: " << max_bw << " Mbps" << std::endl;
        std::cout << "🔹 Minimum Bandwidth: " << min_bw << " Mbps" << std::endl;
        std::cout << "🔹 Bandwidth Range: " << (max_bw - min_bw) << " Mbps" << std::endl;
        std::cout << "🔹 Traffic Volatility: " << volatility << " (" 
                  << (volatility < 0.3 ? "Stable" : volatility < 0.6 ? "Moderate" : "High") << ")" << std::endl;
        std::cout << "🔹 Peak Count: " << peak_count << " detected automatically" << std::endl;
        std::cout << "🔹 Max Gradient: +" << max_grad << " Mbps/hour (acceleration)" << std::endl;
        std::cout << "🔹 Min Gradient: " << min_grad << " Mbps/hour (deceleration)" << std::endl;
        
        // RK4 prediction stats
        double avg_pred = 0;
        for (double pred : rk4_prediction) avg_pred += pred;
        avg_pred /= rk4_prediction.size();
        
        double max_pred = *std::max_element(rk4_prediction.begin(), rk4_prediction.end());
        
        std::cout << "\n🚀 RK4 PREDICTION ANALYSIS:" << std::endl;
        std::cout << "🔹 Predicted Average: " << std::fixed << std::setprecision(3) << avg_pred << " Mbps" << std::endl;
        std::cout << "🔹 Predicted Peak: " << max_pred << " Mbps" << std::endl;
        std::cout << "🔹 Growth Factor: " << (avg_pred / avg_bw) << "x from historical" << std::endl;
        
        std::cout << "\n💡 INSIGHTS:" << std::endl;
        if (volatility < 0.3) {
            std::cout << "✅ Network traffic is STABLE - suitable for predictable capacity planning" << std::endl;
        } else if (volatility < 0.6) {
            std::cout << "⚠️ Network traffic is MODERATE - requires adaptive bandwidth management" << std::endl;
        } else {
            std::cout << "🔴 Network traffic is HIGHLY VARIABLE - needs dynamic QoS controls" << std::endl;
        }
        
        if (max_pred > max_bw * 1.5) {
            std::cout << "📈 RK4 predicts significant traffic GROWTH - consider capacity expansion" << std::endl;
        } else {
            std::cout << "📊 RK4 predicts stable traffic evolution - current capacity adequate" << std::endl;
        }
    }
    
    void generateAllVisualizations() {
        std::cout << "🎨 Generating ASCII Visualizations..." << std::endl;
        std::cout << "📁 Output: Terminal display + text file" << std::endl;
        
        // Display all visualizations
        printBandwidthChart();
        printGradientAnalysis();
        printRK4Comparison();
        printStatisticsSummary();
        
        // Save to file
        saveToFile();
        
        std::cout << "\n✅ ASCII visualizations completed!" << std::endl;
        std::cout << "💡 Screenshots dapat digunakan untuk laporan UAS" << std::endl;
    }
    
private:
    void saveToFile() {
        std::ofstream file("docs/visualizations/ascii_visualization_report.txt");
        
        // Redirect cout to file temporarily
        std::streambuf* orig = std::cout.rdbuf();
        std::cout.rdbuf(file.rdbuf());
        
        std::cout << "METHOD B ANALYSIS - ASCII VISUALIZATION REPORT\n";
        std::cout << "Calvin Wirathama Katoroy - NPM: 2306242395\n";
        std::cout << "Generated: " << __DATE__ << " " << __TIME__ << "\n";
        std::cout << std::string(60, '=') << "\n\n";
        
        printBandwidthChart();
        printGradientAnalysis();
        printRK4Comparison();
        printStatisticsSummary();
        
        // Restore cout
        std::cout.rdbuf(orig);
        file.close();
        
        std::cout << "📄 Report saved: docs/visualizations/ascii_visualization_report.txt" << std::endl;
    }
};

int main() {
    std::cout << "📊 Simple ASCII Visualizer - Method B Analysis" << std::endl;
    std::cout << "Calvin Wirathama Katoroy - NPM: 2306242395" << std::endl;
    std::cout << "No external dependencies required!" << std::endl;
    std::cout << std::string(60, '=') << std::endl;
    
    SimpleVisualizer viz;
    
    if (viz.loadData()) {
        viz.generateAllVisualizations();
    } else {
        std::cout << "❌ Failed to load data. Run enhanced_analyzer first!" << std::endl;
        return 1;
    }
    
    return 0;
}