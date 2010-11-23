#!/bin/bash

for i in `ls`;
do
	echo -ne ${i%.atsp.txt}" ";
	awk "BEGIN
	{
		val = 0; avg = 0; avg_dist = 0; iter = 0; sum_procent = 0;
		split(\"br17 ft53 ft70 ftv170 ftv33 ftv35 ftv38 ftv44 ftv47 ftv55 ftv64 ftv70 kro124p ry48p\", names);
		split(\"39 6905 38673 2755 1286 1473 1530 1613 1776 1608 1839 1960 36230 14422\", values);
		for(i=1; i in names; i++){best_solutions[names[i]] = values[i]};
		
		name = "${i%.atsp.txt}";
		best = best_solutions[name];
	}

	{
		sum += \$2;
		wyniki[iter++] = \$2;
		wynik_procent[iter++] = ((\$2 / best) - 1) * 100
		sum_procent += ((\$2 / best) - 1) * 100;
	}
	END {
		avg = sum / iter;
		avg_dist = sum_procent / iter;
		for (x in wyniki)
		{
			odchylenie = (wyniki[x] - avg) * (wyniki[x] - avg);
			odchylenie_procent = (wyniki_procent[x] - avg_dist) * (wyniki_procent[x] - avg_dist);
		}
		odchylenie = sqrt(odchylenie / iter);
		odchylenie_procent = sqrt(odchylenie_procent / iter);
		printf(\"%s %f %f %f %f\n\", name, avg, odchylenie, avg_dist, odchylenie_procent);
	}" $i ;

done;
