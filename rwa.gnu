set xtics 1
unset ytics
set grid
set xlabel 'Wire Length (m)'
set title 'Random Wire Lengths to Avoid'
set term png size 8000,200
set output 'f.png'
plot 'f' u 1:2:3 with filledcurves palette;

