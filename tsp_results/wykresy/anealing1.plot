#set xrange[0 to 100]
set term postscript eps color
set style data histogram
set style histogram errorbars gap 0 lw 4
set datafile separator " "
set output "anealing1.eps"
set xtics nomirror rotate by -90
set pointsize 1
set xlabel "Instancje problemu" 
set ylabel "Sredni czas wykonywania obliczen [s]"
plot "../simulated_anealing/const_bm/4000_500000/output_anealing" using 7:8:xtic(1) title "4000", \
	"../simulated_anealing/const_bm/16000_500000/output_anealing" using 7:8:xtic(1) title "16000", \
	"../simulated_anealing/const_bm/64000_500000/output_anealing" using 7:8:xtic(1) title "64000", \
	"../simulated_anealing/const_bm/256000_500000/output_anealing" using 7:8:xtic(1) title "256000", \
	"../simulated_anealing/const_bm/1024000_500000/output_anealing" using 7:8:xtic(1) title "1024000", \
	"../simulated_anealing/const_bm/4096000_500000/output_anealing" using 7:8:xtic(1) title "4096000"

