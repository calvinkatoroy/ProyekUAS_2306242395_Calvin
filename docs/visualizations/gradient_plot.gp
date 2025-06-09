set terminal pngcairo enhanced size 1200,600 font 'Arial,12'
set output 'docs/visualizations/gradient_analysis.png'
set title 'Numerical Differentiation Analysis (Part 6)\nGradient = Rate of Change' font 'Arial,14'
set xlabel 'Time (Hour)'
set ylabel 'Gradient (Mbps/hour)'
set grid
set key top right
set xrange [0:23]
set style fill transparent solid 0.3
plot 'docs/visualizations/gradient_data.dat' using 1:2 with lines linewidth 2 title 'Gradient', \
     'docs/visualizations/gradient_data.dat' using 1:3 with filledcurves x1 linecolor rgb 'green' title 'Increasing', \
     'docs/visualizations/gradient_data.dat' using 1:4 with filledcurves x1 linecolor rgb 'red' title 'Decreasing', \
     0 with lines linewidth 1 linecolor rgb 'black' dashtype 2 notitle
