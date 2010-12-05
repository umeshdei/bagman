#set xrange[0 to 100]
set term postscript eps color
set style data histogram
set style histogram errorbars gap 1 lw 4
set datafile separator " "
set output "steepest_greedy_jc.eps"
set xtics nomirror rotate by -90
set pointsize 1
set log y
set xlabel "Instancje problemu" 
set ylabel "Wartosc srednia wspolczynnika jakosc/czas"
plot "../greedy/output_greedy" using 15:16:xticlabels(1) title "Greedy", \
	"../steepest/output_steepest" using 15:16:xticlabels(1) title "Steepest"
	
