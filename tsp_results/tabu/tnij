#!/bin/bash

for i in `find ./ -type d`; do
	if [ $i = "./" ]
	then
		continue;
	fi

#echo -ne "\n$i\n";

	for j in `ls $i`; do
		x=`echo $j | tr '_' '\t' | cut -f1`
		mv $i"/"$j $i"/"$x
	done;
done;
