#!/bin/bash

mkdir data 2>&-
mkdir results 2>&-

mkdir results/greedy 2>&-
mkdir results/steepest 2>&-
mkdir results/random 2>&-
mkdir results/greedy2 2>&-

for s in `seq 1 10`
do
	for i in `seq 1 10`
	do

#		echo generating $i $((s * 50))
#		./Debug/Asimetric_TSP --generate -s $((s * 50)) -o data/input_$((s * 50))_$i.txt

#		continue;				
		echo greedy $i $((s * 50))
		./Debug/Asimetric_TSP -l data/input_$((s * 50))_$i.txt -g -o results/greedy/$((s * 50))_$i -i  2000000 > resulst/greedy/console_out_$((s * 50))_$i.txt
		echo steepest $i $((s * 50))
		./Debug/Asimetric_TSP -l data/input_$((s * 50))_$i.txt -t -o results/steepest/$((s * 50))_$i -i 2000000 > results/steepest/console_out_$((s * 50))_$i.txt
		echo random $i $((s * 50))
		./Debug/Asimetric_TSP -l data/input_$((s * 50))_$i.txt -r -o results/random/$i.$(($s * 50)).$j.txt -i 2000000 > results/random/console_out_$((s * 50))_$i.txt
		echo greedy2 $i $((s * 50))
		./Debug/Asimetric_TSP -l data/input_$((s * 50))_$i.txt -e -o results/greedy2/$((s * 50))_$i -i 2000000 > results/greedy2/console_out_$((s * 50))_$i.txt
	done
done

