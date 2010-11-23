#set xrange[0 to 100]
set term postscript eps color
set style data histogram
set style histogram errorbars gap 1 lw 4
set datafile separator " "
set output "steepest_greedy_steps.eps"
set xtics nomirror rotate by -90
set pointsize 1
set xlabel "Instancje problemu"
set ylabel "Srednia ilosc krokow algorytmu"
plot "../greedy/output_greedy" using 11:12:xticlabels(1) title "Greedy", \
	"../steepest/output_steepest" using 11:12:xticlabels(1) title "Steepest"
	
