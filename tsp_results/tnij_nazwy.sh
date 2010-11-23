#!/bin/bash

for i in `find ./ -iname "console_out_*"`;
do
	x=`echo $i | sed '1,$s/console_out_//g'`;
	mv $i $x;
done;
