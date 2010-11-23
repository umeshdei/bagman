#set xrange[0 to 100]
set term postscript eps color
set style data histogram
set style histogram errorbars gap 0 lw 4
set datafile separator " "
set output "random2.eps"
set xtics nomirror rotate by -90
set pointsize 1
set xlabel "Instancje problemu" 
set ylabel "Sredni czas wykonywania obliczen [s]"
plot "../random/output_random_10000" using 7:8:xtic(1) title "10000", \
	"../random/output_random_50000" using 7:8:xtic(1) title "50000", \
	"../random/output_random_100000" using 7:8:xtic(1) title "100000"
