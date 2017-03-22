set xtics 1
unset ytics
set grid
set xlabel 'Wire Length'
set title 'Random Wire Lengths to Avoid'
set term png size 8000,200
set output 'plot.png'
plot "plot.dat" using 1:2:3 with filledcurves palette;
