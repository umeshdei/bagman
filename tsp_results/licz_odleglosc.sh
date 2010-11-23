#!/bin/bash

	awk "BEGIN {val = 0; avg = 0; iter = 0; }
	{ dist = (\$2 / \$4 - 1) * 100;
	odch = 100 * \$3 / \$2;
	printf(\"%s %f %f\n\", \$0, dist, odch); }" $1 ;

