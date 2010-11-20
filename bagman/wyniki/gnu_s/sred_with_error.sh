#! /bin/sh 
name=$1
echo set title \"Plot $name file with lines and errorbars\" >> tmpgn
echo set ylabel \"Score\" >> tmpgn
echo set xlabel \"T[10*ms]\" >> tmpgn
echo set terminal postscript portrait enhanced mono dashed lw 1 \"Helvetica\" 14 >> tmpgn
echo set output \"$name.ps\" >> tmpgn
echo plot \"$name\"  using 1:2:3 title \'$name\' with yerrorbars, \"$name\" using 1:2 title \'$name\' with lines >> tmpgn

