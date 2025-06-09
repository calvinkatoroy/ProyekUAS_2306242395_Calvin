// Tambahan untuk network_analyzer.h
#ifndef ENHANCED_NETWORK_ANALYZER_H
#define ENHANCED_NETWORK_ANALYZER_H

#include "network_analyzer.h"
#include <cmath>

class EnhancedNetworkAnalyzer : public NetworkAnalyzer {
private:
    std::vector<double> gradients;
    std::vector<double> second_derivatives;
    
public:
    // METHOD B - PART 6: NUMERICAL DIFFERENTIATION
    
    // Forward difference untuk menghitung gradient bandwidth
    double forwardDifference(int index) {
        if (index >= bandwidth.size() - 1) return 0.0;
        return (bandwidth[index + 1] - bandwidth[index]) / 1.0; // h = 1 jam
    }
    
    // Central difference untuk akurasi lebih tinggi
    double centralDifference(int index) {
        if (index <= 0 || index >= bandwidth.size() - 1) return 0.0;
        return (bandwidth[index + 1] - bandwidth[index - 1]) / 2.0; // h = 1 jam
    }
    
    // Second derivative untuk analisis curvature
    double secondDerivative(int index) {
        if (index <= 0 || index >= bandwidth.size() - 1) return 0.0;
        return (bandwidth[index + 1] - 2*bandwidth[index] + bandwidth[index - 1]) / 1.0;
    }
    
    // Analisis rate of change untuk seluruh data
    void calculateGradients() {
        gradients.clear();
        second_derivatives.clear();
        
        for (size_t i = 0; i < bandwidth.size(); i++) {
            gradients.push_back(centralDifference(i));
            second_derivatives.push_back(secondDerivative(i));
        }
        
        std::cout << "\n=== ANALISIS GRADIENT BANDWIDTH ===" << std::endl;
        std::cout << "Jam\tBandwidth\tGradient\tCurvature" << std::endl;
        std::cout << "---\t---------\t--------\t---------" << std::endl;
        
        for (size_t i = 0; i < bandwidth.size(); i++) {
            std::cout << std::fixed << std::setprecision(0) << time_hours[i] 
                      << "\t" << std::setprecision(3) << bandwidth[i]
                      << "\t\t" << gradients[i]
                      << "\t\t" << second_derivatives[i] << std::endl;
        }
    }
    
    // Deteksi peak traffic berdasarkan derivative
    std::vector<int> detectTrafficPeaks() {
        if (gradients.empty()) calculateGradients();
        
        std::vector<int> peaks;
        
        for (size_t i = 1; i < gradients.size() - 1; i++) {
            // Peak condition: gradient berubah dari positif ke negatif
            if (gradients[i-1] > 0.05 && gradients[i+1] < -0.05 && 
                abs(gradients[i]) < 0.1) {
                peaks.push_back(i);
            }
        }
        
        std::cout << "\n=== DETEKSI PEAK TRAFFIC ===" << std::endl;
        for (int peak : peaks) {
            std::cout << "Peak terdeteksi pada jam " << time_hours[peak] 
                      << ":00 dengan bandwidth " << bandwidth[peak] << " Mbps" << std::endl;
        }
        
        return peaks;
    }
    
    // Deteksi anomali berdasarkan gradient threshold
    std::vector<int> detectAnomalies(double threshold = 0.8) {
        if (gradients.empty()) calculateGradients();
        
        std::vector<int> anomalies;
        
        for (size_t i = 0; i < gradients.size(); i++) {
            if (abs(gradients[i]) > threshold) {
                anomalies.push_back(i);
            }
        }
        
        std::cout << "\n=== DETEKSI ANOMALI TRAFFIC ===" << std::endl;
        std::cout << "Threshold gradient: " << threshold << " Mbps/jam" << std::endl;
        
        for (int anomaly : anomalies) {
            std::cout << "Anomali pada jam " << time_hours[anomaly] 
                      << ":00 - Gradient: " << gradients[anomaly] 
                      << " Mbps/jam" << std::endl;
        }
        
        return anomalies;
    }
    
    // METHOD B - PART 7: RUNGE-KUTTA METHODS
    
    // Model dinamika traffic untuk prediksi
    double trafficDynamicsModel(double t, double currentBW) {
        // Model: dB/dt = -decay*B + seasonal_pattern + noise
        double decay = 0.03;
        double amplitude = 1.2;
        double frequency = 2 * M_PI / 24.0;  // 24-hour cycle
        double phase = M_PI / 4;             // Peak pada jam 9-10
        
        return -decay * currentBW + amplitude * sin(frequency * (t - 6) + phase);
    }
    
    // RK4 method untuk prediksi bandwidth masa depan
    double rk4BandwidthPrediction(double t0, double y0, double h, double targetTime) {
        double t = t0;
        double y = y0;
        
        while (t < targetTime) {
            double k1 = h * trafficDynamicsModel(t, y);
            double k2 = h * trafficDynamicsModel(t + h/2, y + k1/2);
            double k3 = h * trafficDynamicsModel(t + h/2, y + k2/2);
            double k4 = h * trafficDynamicsModel(t + h, y + k3);
            
            y += (k1 + 2*k2 + 2*k3 + k4) / 6.0;
            t += h;
            
            // Pastikan bandwidth tetap positif
            if (y < 0.1) y = 0.1;
        }
        return y;
    }
    
    // Prediksi pattern untuk 24 jam ke depan
    std::vector<double> predictNext24Hours() {
        std::vector<double> predictions;
        double lastBandwidth = bandwidth.back();
        double startTime = 24.0; // Mulai dari jam 24 (hari berikutnya)
        
        std::cout << "\n=== PREDIKSI RK4 - 24 JAM KE DEPAN ===" << std::endl;
        std::cout << "Jam\tPrediksi (Mbps)\tInterpretasi" << std::endl;
        std::cout << "---\t---------------\t-----------" << std::endl;
        
        for (int hour = 0; hour < 24; hour++) {
            double targetTime = startTime + hour;
            double predicted = rk4BandwidthPrediction(startTime, lastBandwidth, 0.1, targetTime);
            predictions.push_back(predicted);
            
            // Interpretasi berdasarkan pola
            std::string interpretation;
            if (hour >= 0 && hour <= 5) interpretation = "Malam (rendah)";
            else if (hour >= 6 && hour <= 11) interpretation = "Pagi (meningkat)";
            else if (hour >= 12 && hour <= 17) interpretation = "Siang (tinggi)";
            else interpretation = "Sore (menurun)";
            
            std::cout << std::fixed << std::setprecision(0) << hour 
                      << "\t" << std::setprecision(3) << predicted
                      << "\t\t" << interpretation << std::endl;
        }
        
        return predictions;
    }
    
    // Analisis komprehensif menggunakan semua method B
    void runEnhancedAnalysis() {
        std::cout << "\n" << std::string(60, '=') << std::endl;
        std::cout << "        ANALISIS ENHANCED DENGAN METHOD B" << std::endl;
        std::cout << std::string(60, '=') << std::endl;
        
        // 1. Analisis derivative
        calculateGradients();
        
        // 2. Deteksi peak dan anomali
        auto peaks = detectTrafficPeaks();
        auto anomalies = detectAnomalies(0.6);
        
        // 3. Analisis volatility
        double volatility = calculateVolatility();
        std::cout << "\n=== ANALISIS VOLATILITY ===" << std::endl;
        std::cout << "Traffic Volatility Index: " << std::fixed << std::setprecision(3) 
                  << volatility << std::endl;
        
        if (volatility < 0.3) std::cout << "Status: Traffic stabil" << std::endl;
        else if (volatility < 0.6) std::cout << "Status: Traffic moderat" << std::endl;
        else std::cout << "Status: Traffic sangat variabel" << std::endl;
        
        // 4. Prediksi menggunakan RK4
        auto predictions = predictNext24Hours();
        
        // 5. Perbandingan akurasi
        compareInterpolationMethods();
    }
    
    // Hitung volatility index
    double calculateVolatility() {
        if (gradients.empty()) calculateGradients();
        
        double sumSquaredGradients = 0.0;
        int count = 0;
        
        for (double grad : gradients) {
            if (grad != 0.0) {  // Skip nilai nol di ujung
                sumSquaredGradients += grad * grad;
                count++;
            }
        }
        
        return sqrt(sumSquaredGradients / count);
    }
    
    // Perbandingan metode interpolasi vs RK4
    void compareInterpolationMethods() {
        std::cout << "\n=== PERBANDINGAN METODE PREDIKSI ===" << std::endl;
        std::cout << "Waktu\tLagrange\tRK4\t\tSelisih" << std::endl;
        std::cout << "-----\t--------\t---\t\t-------" << std::endl;
        
        std::vector<double> test_times = {25.5, 27.0, 30.5, 33.0}; // Prediksi masa depan
        
        for (double t : test_times) {
            // Interpolasi Lagrange (extrapolation)
            double lagrange_pred = lagrangeInterpolation(fmod(t, 24.0));
            
            // RK4 prediction
            double rk4_pred = rk4BandwidthPrediction(24.0, bandwidth.back(), 0.1, t);
            
            double difference = abs(lagrange_pred - rk4_pred);
            
            std::cout << std::fixed << std::setprecision(1) << t 
                      << "\t" << std::setprecision(3) << lagrange_pred
                      << "\t\t" << rk4_pred 
                      << "\t\t" << difference << std::endl;
        }
        
        std::cout << "\nKesimpulan:" << std::endl;
        std::cout << "- Lagrange: Baik untuk interpolasi dalam rentang data" << std::endl;
        std::cout << "- RK4: Lebih akurat untuk prediksi jangka panjang" << std::endl;
    }
    
    // Export hasil enhanced analysis
    void exportEnhancedResults(const std::string& filename) {
        std::ofstream outFile(filename);
        
        // Header
        outFile << "Hour,Bandwidth_Mbps,Gradient_Mbps_per_hour,Second_Derivative,RK4_Prediction_Next_Day" << std::endl;
        
        // Hitung gradient jika belum
        if (gradients.empty()) calculateGradients();
        
        // Prediksi untuk hari berikutnya
        auto next_day_predictions = predictNext24Hours();
        
        // Export data
        for (size_t i = 0; i < bandwidth.size(); i++) {
            outFile << time_hours[i] << ","
                    << bandwidth[i] << ","
                    << gradients[i] << ","
                    << second_derivatives[i] << ","
                    << next_day_predictions[i] << std::endl;
        }
        
        outFile.close();
        std::cout << "\nHasil enhanced analysis diekspor ke: " << filename << std::endl;
    }
};

#endif // ENHANCED_NETWORK_ANALYZER_H