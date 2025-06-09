# Enhanced Network Traffic Analyzer - Method B Implementation

---

## 📋 Informasi Utama

**Nama Program:** Enhanced Network Traffic Analyzer

**Metode:** Method B Chapra (Numerical Differentiation & Runge-Kutta Methods)

**Developer:** Calvin Wirathama Katoroy (NPM: 2306242395)

**Kelas:** Sistem Operasi 02, Program Studi Teknik Komputer

**Universitas:** Universitas Indonesia

**Tanggal:** 9 Juni 2025

---

## 🎯 Deskripsi

Aplikasi ini mengimplementasikan **Method B** dari buku *Numerical Methods for Engineers* (Chapra & Canale) untuk analisis lalu lintas jaringan:

* **Part 6 – Numerical Differentiation** : Analisis gradient, deteksi puncak (peak detection), curvature, anomali, dan indeks volatilitas.
* **Part 7 – Runge-Kutta Methods** : Prediksi dinamis 24 jam ke depan menggunakan RK4 dengan model persamaan diferensial untuk traffic.

Hasil analisis mencakup deteksi otomatis 6 puncak traffic, pengukuran indeks volatilitas (0.297), dan prediksi bandwidth (0.100–7.829 Mbps).

---

## 🚀 Fitur Utama

1. **Gradient Analysis** (Central Difference)
2. **Peak Detection** & **Anomaly Detection**
3. **Curvature Analysis** (Second Derivative)
4. **Volatility Index**
5. **Dynamic Prediction** (Runge-Kutta 4th Order)
6. **Comparative Analysis** (RK4 vs Lagrange Interpolation)
7. **Visualisasi** : GnuPlot (PNG) & ASCII Terminal
8. **Menu Interaktif** via terminal CLI

---

## 🛠️ Persiapan & Instalasi

### Prasyarat

* GCC/G++ (C++11 atau lebih tinggi)
* GnuPlot (opsional, untuk output PNG)
* Sistem operasi Windows / Linux / macOS

### Setup Cepat

```bash
# Clone repository
git clone https://github.com/username/ProyekUAS_2306242395_Calvin.git
cd ProyekUAS_2306242395_Calvin

# Build program utama
make                      # Menggunakan Makefile.universal
# atau
g++ -std=c++11 -o enhanced_analyzer src/main.cpp src/network_analyzer.cpp

# (Opsional) Build visualisasi ASCII
g++ -std=c++11 -o simple_vis simple_visualizer.cpp

# (Opsional) Build visualisasi GnuPlot
g++ -std=c++11 -o vis data_visualizer.cpp
```

---

## ⚙️ Cara Menjalankan

1. **Jalankan program utama** :

```bash
   ./enhanced_analyzer
```

1. **Pilih menu** sesuai analisis:
   ```text
   --- PILIHAN ANALISIS METHOD B ---
   1. Muat & proses data mentah
   2. Muat data terproses
   3. Tampilkan statistik dasar
   4. Analisis Gradient & Derivative
   5. Deteksi Peak Traffic
   6. Deteksi Anomali Traffic
   7. Prediksi RK4 - 24 Jam Ke Depan
   8. Analisis Volatility
   9. Perbandingan Lagrange vs RK4
   10. Analisis Komprehensif Lengkap
   11. Export hasil Method B
   0. Keluar
   ```
2. **Generate visualisasi** :

* **ASCII** :
  ``bash ./simple_vis ``
* **PNG** (GnuPlot):
  ```bash
  cd docs/visualizations
  gnuplot bandwidth_plot.gp
  gnuplot gradient_plot.gp
  gnuplot rk4_plot.gp
  ```

--

## 📁 Struktur Direktori

```bash
ProyekUAS_2306242395_Calvin/
├── src/                      # Source code utama
│   ├── main.cpp
│   ├── network_analyzer.cpp
│   └── enhanced_network_analyzer.h
├── data/
│   ├── raw/                  # Dataset mentah (CSV)
│   ├── processed/            # Data preprocessing
│   └── results/              # Output analisis (CSV)
├── docs/
│   └── visualizations/       # Gambar & script GnuPlot
├── Makefile.universal        # Build script
├── simple_visualizer.cpp     # ASCII visualizer
├── data_visualizer.cpp       # GnuPlot visualizer
├── README.md                 # Dokumentasi ini
└── ProyekUAS_2306242395_Calvin.pdf  # Laporan UAS
```

---

## 🖼️ Visualisasi

### Bandwidth vs Time

![Bandwidth Plot](https://i.imgur.com/snAfwAO.png)

### Gradient Analysis

![Gradient Plot](https://i.imgur.com/HdGSGcI.png)

### RK4 Prediction

![RK4 Prediction](https://i.imgur.com/Lts3h3s.png)

---

## 📺 Video Penjelasan


---



## 📚 Referensi

1. Chapra, S. C., & Canale, R. P. (2015). *Numerical Methods for Engineers* (7th ed.). McGraw-Hill Education.
2. University of Cincinnati Network Traffic Dataset.
3. IEEE Conference Template – Overleaf.

---

## 📞 Kontak

**Calvin Wirathama Katoroy**

* Email: [calvin.wirathama@ui.ac.id](mailto:calvin.wirathama@ui.ac.id)
* LinkedIn: linkedin.com/in/calvin-wirathama

---

*Dokumentasi ini disusun untuk Proyek UAS Komputasi Numerik (Jun 2025).*
