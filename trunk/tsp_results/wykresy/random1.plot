#set xrange[0 to 100]
set term postscript eps color
set style data histogram
set style histogram errorbars gap 0 lw 4
set datafile separator " "
set output "random1.eps"
set xtics nomirror rotate by -90
set pointsize 1
set xlabel "Instancje problemu" 
set ylabel "Odleglosc od optimum [%]"
plot "../random/output_random_10000" using 5:6:xtic(1) title "10000", \
	"../random/output_random_30000" using 5:6:xtic(1) title "30000", \
	"../random/output_random_60000" using 5:6:xtic(1) title "60000", \
	"../random/output_random_100000" using 5:6:xtic(1) title "100000"
