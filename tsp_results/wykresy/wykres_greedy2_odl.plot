set term postscript eps color
set output "random1.eps"
#set terminal eps size 1024,600 ; set out 'zad6.eps'
#set linestyle  1 linetype  1 linewidth 8
#set style line 1 line type 1 linewidth 8
set xtics nomirror rotate by -90
set pointsize 2
set xlabel "Instancje problemu" 
set ylabel "Odleglosc od najlepszego znanego rozwiazania"
plot 'output_greedy2_plot' using 4:xtic(1):1 title "" w yerrorbars
