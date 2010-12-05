#set xrange[0 to 100]
set term postscript eps color
set style data histogram
set style histogram errorbars gap 0 lw 4
set datafile separator " "
set output "anealing_tabu_greedy_better.eps"
set xtics nomirror rotate by -90
set pointsize 1
set yrange [0:2100]
set xlabel "Instancje problemu" 
set ylabel "Ilosc popraw rozwiazan w przebiegu dzialania algorytmu"
plot "../simulated_anealing/const_bm/4096000_500000/output_anealing" using 9:10:xtic(1) title "simulated anealing", \
	"../tabu/1000_200_80/output_tabu" using 9:10:xtic(1) title "tabu search", \
	"../greedy/output_greedy" using 9:10:xtic(1) title "greedy", \
	"../steepest/output_steepest" using 9:10:xtic(1) title "steepest"

