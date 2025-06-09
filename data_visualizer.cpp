// data_visualizer.cpp
// Calvin Wirathama Katoroy - NPM: 2306242395
// Visualisasi Data Method B menggunakan C++ + GnuPlot

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include <cstdlib>

class DataVisualizer {
private:
    struct DataPoint {
        double hour;
        double bandwidth;
        double gradient;
        double curvature;
        double rk4_prediction;
        bool is_peak;
    };
    
    std::vector<DataPoint> data;
    std::string output_dir;
    
public:
    DataVisualizer(const std::string& data_file = "data/results/enhanced_analysis_output.csv",
                   const std::string& out_dir = "docs/visualizations/") 
        : output_dir(out_dir) {
        loadData(data_file);
        createOutputDirectory();
    }
    
    bool loadData(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cout << "❌ Error: Cannot open " << filename << std::endl;
            std::cout << "💡 Run the C++ program first to generate data" << std::endl;
            return false;
        }
        
        std::string line;
        std::getline(file, line); // Skip header
        
        while (std::getline(file, line)) {
            DataPoint point;
            std::stringstream ss(line);
            std::string item;
            
            // Parse CSV: Hour,Bandwidth_Mbps,Gradient_Mbps_per_hour,Second_Derivative,RK4_Prediction_Next_Day
            std::getline(ss, item, ','); point.hour = std::stod(item);
            std::getline(ss, item, ','); point.bandwidth = std::stod(item);
            std::getline(ss, item, ','); point.gradient = std::stod(item);
            std::getline(ss, item, ','); point.curvature = std::stod(item);
            std::getline(ss, item, ','); point.rk4_prediction = std::stod(item);
            
            // Detect peaks based on Method B criteria
            point.is_peak = detectPeak(point, data.size());
            
            data.push_back(point);
        }
        
        file.close();
        std::cout << "✅ Data loaded: " << data.size() << " records" << std::endl;
        return true;
    }
    
private:
    bool detectPeak(const DataPoint& current, size_t index) {
        if (index == 0 || index >= data.size()-1) return false;
        
        // Simple peak detection: local maximum with significant bandwidth
        double avg_bandwidth = calculateAverageBandwidth();
        return (current.bandwidth > avg_bandwidth * 1.2 && 
                std::abs(current.gradient) < 0.1);
    }
    
    double calculateAverageBandwidth() {
        if (data.empty()) return 0.0;
        double sum = 0.0;
        for (const auto& point : data) {
            sum += point.bandwidth;
        }
        return sum / data.size();
    }
    
    void createOutputDirectory() {
        std::string command = "mkdir -p " + output_dir;
        system(command.c_str());
    }
    
public:
    void generateBandwidthPlot() {
        std::cout << "📊 Generating Bandwidth Analysis Plot..." << std::endl;
        
        // Generate data file for gnuplot
        std::string data_file = output_dir + "bandwidth_data.dat";
        std::ofstream out(data_file);
        
        out << "# Hour Bandwidth Gradient IsPeak" << std::endl;
        for (const auto& point : data) {
            out << std::fixed << std::setprecision(3)
                << point.hour << " " 
                << point.bandwidth << " "
                << point.gradient << " "
                << (point.is_peak ? 1 : 0) << std::endl;
        }
        out.close();
        
        // Generate gnuplot script
        std::string script_file = output_dir + "bandwidth_plot.gp";
        std::ofstream script(script_file);
        
        script << "set terminal pngcairo enhanced size 1200,800 font 'Arial,12'" << std::endl;
        script << "set output '" << output_dir << "bandwidth_analysis.png'" << std::endl;
        script << "set title 'Network Traffic Analysis - Method B Implementation\\nCalvin Wirathama Katoroy (NPM: 2306242395)' font 'Arial,14'" << std::endl;
        script << "set xlabel 'Time (Hour)'" << std::endl;
        script << "set ylabel 'Bandwidth (Mbps)'" << std::endl;
        script << "set grid" << std::endl;
        script << "set key top right" << std::endl;
        script << "set xrange [0:23]" << std::endl;
        
        script << "plot '" << data_file << "' using 1:2 with linespoints linewidth 2 pointtype 7 title 'Bandwidth', \\" << std::endl;
        script << "     '" << data_file << "' using 1:($4==1?$2:1/0) with points pointtype 13 pointsize 2 linecolor rgb 'red' title 'Detected Peaks'" << std::endl;
        
        script.close();
        
        // Execute gnuplot
        std::string command = "gnuplot " + script_file;
        int result = system(command.c_str());
        
        if (result == 0) {
            std::cout << "✅ Bandwidth plot generated: " << output_dir << "bandwidth_analysis.png" << std::endl;
        } else {
            std::cout << "⚠️  GnuPlot may not be installed. Data file generated: " << data_file << std::endl;
        }
    }
    
    void generateGradientPlot() {
        std::cout << "📈 Generating Gradient Analysis Plot..." << std::endl;
        
        std::string data_file = output_dir + "gradient_data.dat";
        std::ofstream out(data_file);
        
        out << "# Hour Gradient Positive Negative" << std::endl;
        for (const auto& point : data) {
            out << std::fixed << std::setprecision(3)
                << point.hour << " " 
                << point.gradient << " "
                << (point.gradient > 0 ? point.gradient : 0) << " "
                << (point.gradient < 0 ? point.gradient : 0) << std::endl;
        }
        out.close();
        
        std::string script_file = output_dir + "gradient_plot.gp";
        std::ofstream script(script_file);
        
        script << "set terminal pngcairo enhanced size 1200,600 font 'Arial,12'" << std::endl;
        script << "set output '" << output_dir << "gradient_analysis.png'" << std::endl;
        script << "set title 'Numerical Differentiation Analysis (Part 6)\\nGradient = Rate of Change' font 'Arial,14'" << std::endl;
        script << "set xlabel 'Time (Hour)'" << std::endl;
        script << "set ylabel 'Gradient (Mbps/hour)'" << std::endl;
        script << "set grid" << std::endl;
        script << "set key top right" << std::endl;
        script << "set xrange [0:23]" << std::endl;
        script << "set style fill transparent solid 0.3" << std::endl;
        
        script << "plot '" << data_file << "' using 1:2 with lines linewidth 2 title 'Gradient', \\" << std::endl;
        script << "     '" << data_file << "' using 1:3 with filledcurves x1 linecolor rgb 'green' title 'Increasing', \\" << std::endl;
        script << "     '" << data_file << "' using 1:4 with filledcurves x1 linecolor rgb 'red' title 'Decreasing', \\" << std::endl;
        script << "     0 with lines linewidth 1 linecolor rgb 'black' dashtype 2 notitle" << std::endl;
        
        script.close();
        
        std::string command = "gnuplot " + script_file;
        int result = system(command.c_str());
        
        if (result == 0) {
            std::cout << "✅ Gradient plot generated: " << output_dir << "gradient_analysis.png" << std::endl;
        } else {
            std::cout << "⚠️  GnuPlot may not be installed. Data file generated: " << data_file << std::endl;
        }
    }
    
    void generateRK4PredictionPlot() {
        std::cout << "🚀 Generating RK4 Prediction Plot..." << std::endl;
        
        std::string data_file = output_dir + "rk4_data.dat";
        std::ofstream out(data_file);
        
        out << "# Hour Historical Prediction" << std::endl;
        
        // Historical data (0-23)
        for (const auto& point : data) {
            out << std::fixed << std::setprecision(3)
                << point.hour << " " 
                << point.bandwidth << " "
                << "NaN" << std::endl;
        }
        
        // Prediction data (24-47)
        for (size_t i = 0; i < data.size(); i++) {
            out << std::fixed << std::setprecision(3)
                << (24 + i) << " "
                << "NaN" << " "
                << data[i].rk4_prediction << std::endl;
        }
        
        out.close();
        
        std::string script_file = output_dir + "rk4_plot.gp";
        std::ofstream script(script_file);
        
        script << "set terminal pngcairo enhanced size 1400,800 font 'Arial,12'" << std::endl;
        script << "set output '" << output_dir << "rk4_prediction.png'" << std::endl;
        script << "set title 'Runge-Kutta 4th Order Prediction (Part 7)\\nDynamic Traffic Forecasting - Method B' font 'Arial,14'" << std::endl;
        script << "set xlabel 'Time (Hour)'" << std::endl;
        script << "set ylabel 'Bandwidth (Mbps)'" << std::endl;
        script << "set grid" << std::endl;
        script << "set key top right" << std::endl;
        script << "set xrange [0:47]" << std::endl;
        
        // Add vertical line to separate historical vs prediction
        script << "set arrow from 23.5, graph 0 to 23.5, graph 1 nohead linetype 3 linewidth 2 linecolor rgb 'gray'" << std::endl;
        script << "set label 'Historical Data' at 11.5, graph 0.9 center font 'Arial,12'" << std::endl;
        script << "set label 'RK4 Prediction' at 35.5, graph 0.9 center font 'Arial,12'" << std::endl;
        
        script << "plot '" << data_file << "' using 1:2 with linespoints linewidth 3 pointtype 7 title 'Historical Data (Day 1)', \\" << std::endl;
        script << "     '" << data_file << "' using 1:3 with linespoints linewidth 3 pointtype 9 linecolor rgb 'red' title 'RK4 Prediction (Day 2)'" << std::endl;
        
        script.close();
        
        std::string command = "gnuplot " + script_file;
        int result = system(command.c_str());
        
        if (result == 0) {
            std::cout << "✅ RK4 prediction plot generated: " << output_dir << "rk4_prediction.png" << std::endl;
        } else {
            std::cout << "⚠️  GnuPlot may not be installed. Data file generated: " << data_file << std::endl;
        }
    }
    
    void generateTextBasedPlots() {
        std::cout << "📊 Generating Text-Based Visualizations..." << std::endl;
        
        std::string text_file = output_dir + "text_visualizations.txt";
        std::ofstream out(text_file);
        
        out << "=========================================" << std::endl;
        out << "    METHOD B ANALYSIS VISUALIZATION" << std::endl;
        out << "    Calvin Wirathama Katoroy" << std::endl;
        out << "    NPM: 2306242395" << std::endl;
        out << "=========================================" << std::endl;
        
        // Bandwidth bar chart
        out << "\n📊 BANDWIDTH DISTRIBUTION (24 HOURS):" << std::endl;
        out << "Hour |Bandwidth |Graph" << std::endl;
        out << "-----|----------|" << std::string(50, '-') << std::endl;
        
        double max_bandwidth = 0;
        for (const auto& point : data) {
            max_bandwidth = std::max(max_bandwidth, point.bandwidth);
        }
        
        for (const auto& point : data) {
            int bar_length = static_cast<int>((point.bandwidth / max_bandwidth) * 40);
            std::string bar(bar_length, '█');
            
            out << std::setw(4) << static_cast<int>(point.hour) << " |"
                << std::setw(9) << std::fixed << std::setprecision(3) << point.bandwidth << " |"
                << bar;
            
            if (point.is_peak) {
                out << " ← PEAK";
            }
            out << std::endl;
        }
        
        // Gradient analysis
        out << "\n📈 GRADIENT ANALYSIS:" << std::endl;
        out << "Hour |Gradient  |Trend" << std::endl;
        out << "-----|----------|-----" << std::endl;
        
        for (const auto& point : data) {
            std::string trend;
            if (point.gradient > 0.1) trend = "↗ Increasing";
            else if (point.gradient < -0.1) trend = "↘ Decreasing";
            else trend = "→ Stable";
            
            out << std::setw(4) << static_cast<int>(point.hour) << " |"
                << std::setw(9) << std::fixed << std::setprecision(3) << point.gradient << " |"
                << trend << std::endl;
        }
        
        // Statistics summary
        double volatility = calculateVolatility();
        int peak_count = std::count_if(data.begin(), data.end(), 
                                      [](const DataPoint& p) { return p.is_peak; });
        
        out << "\n📊 STATISTICS SUMMARY:" << std::endl;
        out << "• Total Data Points: " << data.size() << std::endl;
        out << "• Average Bandwidth: " << std::fixed << std::setprecision(3) 
            << calculateAverageBandwidth() << " Mbps" << std::endl;
        out << "• Peak Bandwidth: " << getMaxBandwidth() << " Mbps" << std::endl;
        out << "• Traffic Volatility Index: " << volatility << std::endl;
        out << "• Peak Count Detected: " << peak_count << std::endl;
        out << "• Traffic Status: " << (volatility < 0.3 ? "Stable" : 
                                       volatility < 0.6 ? "Moderate" : "High Volatility") << std::endl;
        
        out.close();
        
        std::cout << "✅ Text visualization generated: " << text_file << std::endl;
    }
    
private:
    double calculateVolatility() {
        if (data.empty()) return 0.0;
        
        double sum_squared = 0.0;
        int count = 0;
        
        for (const auto& point : data) {
            if (point.gradient != 0.0) {
                sum_squared += point.gradient * point.gradient;
                count++;
            }
        }
        
        return count > 0 ? std::sqrt(sum_squared / count) : 0.0;
    }
    
    double getMaxBandwidth() {
        if (data.empty()) return 0.0;
        return std::max_element(data.begin(), data.end(),
                               [](const DataPoint& a, const DataPoint& b) {
                                   return a.bandwidth < b.bandwidth;
                               })->bandwidth;
    }
    
public:
    void generateAllPlots() {
        std::cout << "🎨 Generating all visualizations using C++..." << std::endl;
        std::cout << "📁 Output directory: " << output_dir << std::endl;
        
        // Generate GnuPlot-based plots
        generateBandwidthPlot();
        generateGradientPlot();
        generateRK4PredictionPlot();
        
        // Generate text-based visualizations (backup)
        generateTextBasedPlots();
        
        // Generate CSV files for external tools
        generateCSVForExternalTools();
        
        std::cout << "\n✅ All visualizations generated!" << std::endl;
        std::cout << "📊 Files ready untuk laporan UAS" << std::endl;
        
        // Instructions for user
        std::cout << "\n💡 INSTRUCTIONS:" << std::endl;
        std::cout << "1. Install GnuPlot jika belum ada: apt-get install gnuplot" << std::endl;
        std::cout << "2. PNG files akan di-generate otomatis" << std::endl;
        std::cout << "3. CSV files tersedia untuk Excel/external tools" << std::endl;
        std::cout << "4. Text visualization tersedia sebagai backup" << std::endl;
    }
    
    void generateCSVForExternalTools() {
        // Summary data untuk plotting external
        std::string csv_file = output_dir + "plot_data_summary.csv";
        std::ofstream out(csv_file);
        
        out << "Hour,Bandwidth_Mbps,Gradient,Curvature,RK4_Prediction,Peak_Indicator" << std::endl;
        
        for (const auto& point : data) {
            out << std::fixed << std::setprecision(3)
                << point.hour << ","
                << point.bandwidth << ","
                << point.gradient << ","
                << point.curvature << ","
                << point.rk4_prediction << ","
                << (point.is_peak ? 1 : 0) << std::endl;
        }
        
        out.close();
        std::cout << "✅ CSV for external tools: " << csv_file << std::endl;
    }
    
    void displaySummary() {
        std::cout << "\n📊 METHOD B ANALYSIS SUMMARY:" << std::endl;
        std::cout << "================================" << std::endl;
        
        double volatility = calculateVolatility();
        int peak_count = std::count_if(data.begin(), data.end(), 
                                      [](const DataPoint& p) { return p.is_peak; });
        
        auto max_gradient = std::max_element(data.begin(), data.end(),
                                           [](const DataPoint& a, const DataPoint& b) {
                                               return a.gradient < b.gradient;
                                           });
        
        auto min_gradient = std::min_element(data.begin(), data.end(),
                                           [](const DataPoint& a, const DataPoint& b) {
                                               return a.gradient < b.gradient;
                                           });
        
        std::cout << "🔹 Dataset: " << data.size() << " hourly data points" << std::endl;
        std::cout << "🔹 Traffic Volatility: " << std::fixed << std::setprecision(3) 
                  << volatility << " (" << (volatility < 0.3 ? "Stable" : "Variable") << ")" << std::endl;
        std::cout << "🔹 Peaks Detected: " << peak_count << " automatic detection" << std::endl;
        std::cout << "🔹 Max Gradient: +" << max_gradient->gradient << " Mbps/h (hour " 
                  << static_cast<int>(max_gradient->hour) << ")" << std::endl;
        std::cout << "🔹 Min Gradient: " << min_gradient->gradient << " Mbps/h (hour " 
                  << static_cast<int>(min_gradient->hour) << ")" << std::endl;
        std::cout << "🔹 Peak Bandwidth: " << getMaxBandwidth() << " Mbps" << std::endl;
        std::cout << "🔹 Average Bandwidth: " << calculateAverageBandwidth() << " Mbps" << std::endl;
    }
};

int main() {
    std::cout << "🎨 C++ Data Visualizer - Method B Analysis" << std::endl;
    std::cout << "Calvin Wirathama Katoroy - NPM: 2306242395" << std::endl;
    std::cout << "==========================================" << std::endl;
    
    DataVisualizer visualizer;
    
    // Display analysis summary
    visualizer.displaySummary();
    
    // Generate all visualizations
    visualizer.generateAllPlots();
    
    std::cout << "\n🎯 Visualization completed!" << std::endl;
    std::cout << "💡 Use generated files untuk laporan UAS" << std::endl;
    
    return 0;
}