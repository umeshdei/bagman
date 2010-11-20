#! /bin/sh 
name=$1
echo set title \"Plot $name - best run\" >> tmpgn
echo set ylabel \"Distance from optimum [%]\" >> tmpgn
echo set xlabel \"Dataset\" >> tmpgn
echo set xtics nomirror rotate by -90 >> tmpgn
echo set terminal postscript portrait enhanced mono dashed lw 1 \"Helvetica\" 14 >> tmpgn
echo set output \"$name.ps\" >> tmpgn
echo plot \"$name\" using 2:xtic\(1\) title \'$name\' with lines >> tmpgn

