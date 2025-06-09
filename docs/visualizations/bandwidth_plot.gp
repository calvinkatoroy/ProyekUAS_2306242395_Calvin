set terminal pngcairo enhanced size 1200,800 font 'Arial,12'
set output 'docs/visualizations/bandwidth_analysis.png'
set title 'Network Traffic Analysis - Method B Implementation\nCalvin Wirathama Katoroy (NPM: 2306242395)' font 'Arial,14'
set xlabel 'Time (Hour)'
set ylabel 'Bandwidth (Mbps)'
set grid
set key top right
set xrange [0:23]
plot 'docs/visualizations/bandwidth_data.dat' using 1:2 with linespoints linewidth 2 pointtype 7 title 'Bandwidth', \
     'docs/visualizations/bandwidth_data.dat' using 1:($4==1?$2:1/0) with points pointtype 13 pointsize 2 linecolor rgb 'red' title 'Detected Peaks'
