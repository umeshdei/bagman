#set xrange[0 to 100]
set term postscript eps color
set style data histogram
set style histogram errorbars gap 0 lw 4
set datafile separator " "
set output "anealing2.eps"
set xtics nomirror rotate by -90
set pointsize 1
set yrange [0:300] 
set xlabel "Instancje problemu" 
set ylabel "Odleglosc od optimum [%]"
plot "../simulated_anealing/const_bm/256000_500000/output_anealing" using 5:6:xtic(1) title "256000", \
	"../simulated_anealing/const_bm/1024000_500000/output_anealing" using 5:6:xtic(1) title "1024000", \
	"../simulated_anealing/const_bm/4096000_500000/output_anealing" using 5:6:xtic(1) title "4096000"

