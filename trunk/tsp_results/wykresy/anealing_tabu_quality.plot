#set xrange[0 to 100]
set term postscript eps color
set style data histogram
set style histogram errorbars gap 0 lw 4
set datafile separator " "
set output "anealing_tabu_quality.eps"
set xtics nomirror rotate by -90
set pointsize 1
set yrange [0:180] 
set xlabel "Instancje problemu" 
set ylabel "Odleglosc od optimum [%]"
plot "../simulated_anealing/const_bm/4096000_500000/output_anealing" using 5:6:xtic(1) title "simulated anealing", \
	"../tabu/1000_200_80/output_tabu" using 5:6:xtic(1) title "tabu search"

