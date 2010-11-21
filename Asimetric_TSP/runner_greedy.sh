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

#               echo generating $i $((s * 50))
#               ./Debug/Asimetric_TSP --generate -s $((s * 50)) -o data/input_$((s * 50))_$i.txt

#               continue;                               
                echo greedy $i $((s * 50))
                ./Debug/Asimetric_TSP -l data/input_$((s * 50))_$i.txt -g -o results/greedy/$((s * 50))_$i.txt -i  2000000 > resulst/greedy/console_out_$((s * 50))_$i.txt
        done
done

