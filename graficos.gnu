set terminal postscript landscape enhanced defaultplex \
	leveldefault color colortext \
	solid dashlength 1.0 linewidth 1.0 butt noclip \
	nobackground \
	palfuncparam 2000,0.003 \
	"Helvetica" 14 fontscale 1.0

set output "conteo.eps"

f(x) = a * x**b

fit f(x) 'promedios.dat' using 1:2 via a, b

set xlabel "r[Mpc]"
set ylabel "Numero de galaxias"

set xrange [0:190]
set yrange [0:20000]

plot 'promedios.dat' u 1:2 w p pt 7 ps 0.8 lc -1 notitle, f(x) lt rgb "red"  lw 3 notitle

set output "correlacion.eps"

set xlabel "r[Mpc]"
set ylabel "Dimension"

set xrange[0:350]
set yrange[0.0:3.5]

f(x) = 2.0
g(x) = 3.0

plot 'D2.dat' using 1:2 w l lw 1 lc -1 notitle, f(x) dt 2 lw 2 lc 18 notitle, g(x) dt 2 lw 2 lc 20 notitle
