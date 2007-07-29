set grid

set terminal png
set output '../synthetic/2/rect/rect.png'
set title ""
set xlabel ""
set ylabel ""
set xrange [0:1]
set yrange [0:1]

plot '../synthetic/2/rect/rect01.dat' using 1:2 title "1" with points, \
     '../synthetic/2/rect/rect02.dat' using 1:2 title "2" with points

