set terminal postscript eps enhanced
set output "conteo.eps"

f(x) = a * x**b

fit f(x) 'promedios.dat' using 1:2 via a, b

set title "D = 2.4104"

set xlabel "r[Mpc]"
set ylabel "Nro de galaxias"

set xrange [0:200]
set yrange [0:26000]

plot 'promedios.dat' u 1:2, f(x)
