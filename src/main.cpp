// Enhanced main.cpp dengan Method B
#include "network_analyzer.h"
#include "enhanced_network_analyzer.h"
#include <iostream>
#include <string>

void printEnhancedHeader() {
    std::cout << "=============================================" << std::endl;
    std::cout << "  PROGRAM ANALISIS LALU LINTAS JARINGAN" << std::endl;
    std::cout << "  ENHANCED DENGAN METHOD B (CHAPRA)" << std::endl;
    std::cout << "  Numerical Differentiation + Runge-Kutta" << std::endl;
    std::cout << "  Dataset Universitas Cincinnati" << std::endl;
    std::cout << "=============================================" << std::endl;
    std::cout << "  Developer: Calvin Wirathama Katoroy" << std::endl;
    std::cout << "  NPM: 2306242395" << std::endl;
    std::cout << "  Kelas: Sistem Operasi 02" << std::endl;
    std::cout << "=============================================" << std::endl;
}

void printEnhancedMenu() {
    std::cout << "\n--- PILIHAN ANALISIS METHOD B ---" << std::endl;
    std::cout << "1. Muat dan proses data mentah (output1.csv)" << std::endl;
    std::cout << "2. Muat data yang sudah diproses" << std::endl;
    std::cout << "3. Tampilkan statistik dasar" << std::endl;
    std::cout << "4. [METHOD B] Analisis Gradient & Derivative" << std::endl;
    std::cout << "5. [METHOD B] Deteksi Peak Traffic" << std::endl;
    std::cout << "6. [METHOD B] Deteksi Anomali Traffic" << std::endl;
    std::cout << "7. [METHOD B] Prediksi RK4 - 24 Jam Ke Depan" << std::endl;
    std::cout << "8. [METHOD B] Analisis Volatility" << std::endl;
    std::cout << "9. [METHOD B] Perbandingan Lagrange vs RK4" << std::endl;
    std::cout << "10. [METHOD B] Analisis Komprehensif Lengkap" << std::endl;
    std::cout << "11. Export hasil Method B" << std::endl;
    std::cout << "0. Keluar" << std::endl;
    std::cout << "Pilihan: ";
}

void demonstrateMethodB(EnhancedNetworkAnalyzer& analyzer) {
    std::cout << "\n" << std::string(50, '=') << std::endl;
    std::cout << "     DEMONSTRASI METHOD B - CHAPRA" << std::endl;
    std::cout << "     Calvin Wirathama Katoroy - NPM: 2306242395" << std::endl;
    std::cout << "     Kelas: Sistem Operasi 02" << std::endl;
    std::cout << std::string(50, '=') << std::endl;
    
    std::cout << "\nMETHOD B terdiri dari:" << std::endl;
    std::cout << "• Part 6 - Numerical Differentiation (Gradient Analysis)" << std::endl;
    std::cout << "• Part 7 - Runge-Kutta Methods (Dynamic Prediction)" << std::endl;
    
    std::cout << "\n🔍 1. Analisis Derivative untuk Rate of Change..." << std::endl;
    analyzer.calculateGradients();
    
    std::cout << "\n📈 2. Deteksi Peak menggunakan Derivative..." << std::endl;
    analyzer.detectTrafficPeaks();
    
    std::cout << "\n🚀 3. Prediksi Dynamic menggunakan RK4..." << std::endl;
    analyzer.predictNext24Hours();
    
    std::cout << "\n📊 4. Analisis Volatility Traffic..." << std::endl;
    double volatility = analyzer.calculateVolatility();
    std::cout << "Traffic Volatility Index: " << std::fixed << std::setprecision(3) 
              << volatility << std::endl;
}

int main() {
    printEnhancedHeader();
    
    EnhancedNetworkAnalyzer analyzer;
    bool dataLoaded = false;
    int choice;
    
    while (true) {
        printEnhancedMenu();
        std::cin >> choice;
        
        switch (choice) {
            case 1: {
                std::cout << "\nMemuat data mentah dari data/raw/output1.csv..." << std::endl;
                if (analyzer.loadRawData("data/raw/output1.csv")) {
                    std::cout << "✓ Data mentah berhasil dimuat dan diproses!" << std::endl;
                    analyzer.saveProcessedData("data/processed/network_traffic_timeseries.csv");
                    dataLoaded = true;
                } else {
                    std::cout << "✗ Gagal memuat data mentah. Periksa lokasi file." << std::endl;
                }
                break;
            }
            
            case 2: {
                std::cout << "\nMemuat data yang sudah diproses..." << std::endl;
                if (analyzer.loadProcessedData("data/processed/network_traffic_timeseries.csv")) {
                    std::cout << "✓ Data terproses berhasil dimuat!" << std::endl;
                    dataLoaded = true;
                } else {
                    std::cout << "✗ Gagal memuat data terproses." << std::endl;
                }
                break;
            }
            
            case 3: {
                if (!dataLoaded) {
                    std::cout << "❌ Silakan muat data terlebih dahulu (pilihan 1 atau 2)." << std::endl;
                    break;
                }
                analyzer.calculateStatistics();
                break;
            }
            
            case 4: {
                if (!dataLoaded) {
                    std::cout << "❌ Silakan muat data terlebih dahulu (pilihan 1 atau 2)." << std::endl;
                    break;
                }
                std::cout << "\n🔍 [METHOD B - PART 6] ANALISIS GRADIENT & DERIVATIVE" << std::endl;
                analyzer.calculateGradients();
                break;
            }
            
            case 5: {
                if (!dataLoaded) {
                    std::cout << "❌ Silakan muat data terlebih dahulu (pilihan 1 atau 2)." << std::endl;
                    break;
                }
                std::cout << "\n📈 [METHOD B - PART 6] DETEKSI PEAK TRAFFIC" << std::endl;
                analyzer.detectTrafficPeaks();
                break;
            }
            
            case 6: {
                if (!dataLoaded) {
                    std::cout << "❌ Silakan muat data terlebih dahulu (pilihan 1 atau 2)." << std::endl;
                    break;
                }
                std::cout << "\n⚠️  [METHOD B - PART 6] DETEKSI ANOMALI TRAFFIC" << std::endl;
                double threshold;
                std::cout << "Masukkan threshold gradient (default 0.6): ";
                std::cin >> threshold;
                analyzer.detectAnomalies(threshold);
                break;
            }
            
            case 7: {
                if (!dataLoaded) {
                    std::cout << "❌ Silakan muat data terlebih dahulu (pilihan 1 atau 2)." << std::endl;
                    break;
                }
                std::cout << "\n🚀 [METHOD B - PART 7] PREDIKSI RK4 - 24 JAM KE DEPAN" << std::endl;
                analyzer.predictNext24Hours();
                break;
            }
            
            case 8: {
                if (!dataLoaded) {
                    std::cout << "❌ Silakan muat data terlebih dahulu (pilihan 1 atau 2)." << std::endl;
                    break;
                }
                std::cout << "\n📊 [METHOD B] ANALISIS VOLATILITY" << std::endl;
                double volatility = analyzer.calculateVolatility();
                std::cout << "Traffic Volatility Index: " << std::fixed << std::setprecision(3) 
                          << volatility << std::endl;
                
                if (volatility < 0.3) std::cout << "Status: 🟢 Traffic stabil" << std::endl;
                else if (volatility < 0.6) std::cout << "Status: 🟡 Traffic moderat" << std::endl;
                else std::cout << "Status: 🔴 Traffic sangat variabel" << std::endl;
                break;
            }
            
            case 9: {
                if (!dataLoaded) {
                    std::cout << "❌ Silakan muat data terlebih dahulu (pilihan 1 atau 2)." << std::endl;
                    break;
                }
                std::cout << "\n⚖️  [METHOD B] PERBANDINGAN LAGRANGE vs RK4" << std::endl;
                analyzer.compareInterpolationMethods();
                break;
            }
            
            case 10: {
                if (!dataLoaded) {
                    std::cout << "❌ Silakan muat data terlebih dahulu (pilihan 1 atau 2)." << std::endl;
                    break;
                }
                std::cout << "\n🎯 [METHOD B] ANALISIS KOMPREHENSIF LENGKAP" << std::endl;
                analyzer.runEnhancedAnalysis();
                break;
            }
            
            case 11: {
                if (!dataLoaded) {
                    std::cout << "❌ Silakan muat data terlebih dahulu (pilihan 1 atau 2)." << std::endl;
                    break;
                }
                std::cout << "\n💾 EXPORT HASIL METHOD B" << std::endl;
                analyzer.exportEnhancedResults("data/results/enhanced_analysis_output.csv");
                break;
            }
            
            case 0: {
                std::cout << "\n🎉 Terima kasih telah menggunakan Enhanced Network Analyzer!" << std::endl;
                std::cout << "Method B (Numerical Differentiation + Runge-Kutta) telah berhasil diimplementasikan." << std::endl;
                std::cout << "\n📋 Informasi Developer:" << std::endl;
                std::cout << "Nama: Calvin Wirathama Katoroy" << std::endl;
                std::cout << "NPM: 2306242395" << std::endl;
                std::cout << "Kelas: Sistem Operasi 02" << std::endl;
                std::cout << "\n🚀 Method B berhasil menganalisis " << std::endl;
                std::cout << "✓ Numerical Differentiation untuk gradient analysis" << std::endl;
                std::cout << "✓ Runge-Kutta untuk dynamic prediction" << std::endl;
                std::cout << "✓ Peak detection & anomaly analysis" << std::endl;
                return 0;
            }
            
            default: {
                std::cout << "❌ Pilihan tidak valid. Silakan coba lagi." << std::endl;
                break;
            }
        }
        
        // Pause untuk melihat hasil
        std::cout << "\nTekan Enter untuk melanjutkan...";
        std::cin.ignore();
        std::cin.get();
    }
    
    return 0;
}