#!/bin/bash

mkdir data
mkdir results

mkdir results/greedy
mkdir results/steepest
mkdir results/random
mkdir results/greedy2

exit;
for s in `seq 1 10`
do
	for i in `seq 1 10`
	do
		./Debug/Asimetric_TSP -g -s $((s * 50)) -o data/input_$((s * 50))_$i.txt
				
		echo greedy $i $((s * 50))
		./Debug/Asimetric_TSP -l data/input_$((s * 50))_$i.txt -e -o results/greedy/$((s * 50))_$i.txt
		echo steepest $i $((s * 50))
		./Debug/Asimetric_TSP -l data/input_$((s * 50))_$i.txt -t -o results/steepest/$i.$((s * 50)).$j.txt
		echo random $i $((s * 50))
		./Debug/Asimetric_TSP -l data/input_$((s * 50))_$i.txt -r -o results/random/$i.$(($s * 50)).$j.txt -i $(($j * 20000))
		echo greedy2 $i $((s * 50))
		./Debug/Asimetric_TSP -l data/input_$((s * 50))_$i.txt -w -o results/greedy2/$i.$((s * 50)).$j.txt
	done
done

