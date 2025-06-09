set terminal pngcairo enhanced size 1400,800 font 'Arial,12'
set output 'docs/visualizations/rk4_prediction.png'
set title 'Runge-Kutta 4th Order Prediction (Part 7)\nDynamic Traffic Forecasting - Method B' font 'Arial,14'
set xlabel 'Time (Hour)'
set ylabel 'Bandwidth (Mbps)'
set grid
set key top right
set xrange [0:47]
set arrow from 23.5, graph 0 to 23.5, graph 1 nohead linetype 3 linewidth 2 linecolor rgb 'gray'
set label 'Historical Data' at 11.5, graph 0.9 center font 'Arial,12'
set label 'RK4 Prediction' at 35.5, graph 0.9 center font 'Arial,12'
plot 'docs/visualizations/rk4_data.dat' using 1:2 with linespoints linewidth 3 pointtype 7 title 'Historical Data (Day 1)', \
     'docs/visualizations/rk4_data.dat' using 1:3 with linespoints linewidth 3 pointtype 9 linecolor rgb 'red' title 'RK4 Prediction (Day 2)'
