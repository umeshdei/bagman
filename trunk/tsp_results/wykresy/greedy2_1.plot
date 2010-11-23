#set xrange[0 to 100]
#set title "Plot ../greedy2/output_greedy2 file with lines and errorbars"
set term postscript eps color
set style data histogram
set style histogram errorbars gap 1 lw 4
set datafile separator " "
set output "greedy2_1.eps"
set xtics nomirror rotate by -90
set pointsize 1
set xlabel "Instancje problemu" 
set ylabel "Odleglosc od optimum [%]"
plot "../greedy2/output_greedy2" using 5:6:xticlabels(1) title "rozwiazanie autorskie"
