set term postscript eps enhanced
set output "correlacion.eps"

set xlabel "r[Mpc]"
set ylabel "Dimension"

set xrange[0:350]
set yrange[0.0:3.5]

f(x) = 2.0
g(x) = 3.0

plot 'D2.dat' using 1:2 w l, f(x), g(x)
