#!/bin/bash

for i in `ls $1*.atsp`;
do
	name=${i%.atsp};
	name=${name#*\/}
	name=${name#*\/}
	awk "BEGIN {
		val = 0; avg = 0; avg_dist = 0; iter = 0; sum_procent = 0;
		sum_time = 0;
		sum_better_solutions = 0;
		sum_steps_count = 0;
		sum_neighbors_visit = 0;
		split(\"br17 ft53 ft70 ftv170 ftv33 ftv35 ftv38 ftv44 ftv47 ftv55 ftv64 ftv70 kro124p ry48p rbg323 rbg358 rbg403 rbg443 kro124 p43\", names);
		split(\"39 6905 38673 2755 1286 1473 1530 1613 1776 1608 1839 1960 36230 14422 1326 1163 2465 2720 36230 5620\", values);
		for(i=1; i in names; i++){best_solutions[names[i]] = values[i]};
		
		name=\"$name\";
		best = best_solutions[name];
	}

	{
		if (best != 0)
		{
			sum += \$2;
			wyniki[iter] = \$2;
			wynik_procent[iter] = ((\$2 / best) - 1) * 100
			sum_procent += ((\$2 / best) - 1) * 100;
			wyniki_time[iter] = \$1;
			sum_time += \$1;
			better_solutions[iter] = \$4;
			sum_better_solutions += \$4;
			steps_count[iter] = \$5;
			sum_steps_count += \$5;
			neighbors_visit[iter] = \$6;
			sum_neighbors_visit += \$6;
			iter++;
		}
	}

	END {
		avg = sum / iter;
		avg_dist = sum_procent / iter;
		avg_time = sum_time / iter;
		avg_better_solutions = sum_better_solutions / iter;
		avg_steps = sum_steps_count / iter;
		avg_neighbors = sum_neighbors_visit / iter;
		for (x in wyniki)
		{
			odchylenie += (wyniki[x] - avg) * (wyniki[x] - avg);
			odchylenie_procent += (wynik_procent[x] - avg_dist) * (wynik_procent[x] - avg_dist);
			odchylenie_time += (wyniki_time[x] - avg_time) * (wyniki_time[x] - avg_time);
			odchylenie_better_solutions += (better_solutions[x] - avg_better_solutions) * (better_solutions[x] - avg_better_solutions);
			odchylenie_steps += (steps_count[x] - avg_steps) * (steps_count[x] - avg_steps);
			odchylenie_neighbors += (neighbors_visit[x] - avg_neighbors) * (neighbors_visit[x] - avg_neighbors);
		}
		odchylenie = sqrt(odchylenie) / iter;
		odchylenie_procent = sqrt(odchylenie_procent) / iter;
		odchylenie_time = sqrt(odchylenie_time) / iter;
		odchylenie_better_solutions = sqrt(odchylenie_better_solutions) / iter;
		odchylenie_steps = sqrt(odchylenie_steps) / iter;
		odchylenie_neighbors = sqrt(odchylenie_neighbors) / iter;
		jakosc_czas = avg_dist * avg_time;
		odchylenie_jakosc_czas = odchylenie_time * odchylenie_procent;
		printf(\"%s %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f\n\", name, avg, best, odchylenie, avg_dist, odchylenie_procent,
			avg_time, odchylenie_time, avg_better_solutions, odchylenie_better_solutions,
			avg_steps, odchylenie_steps, avg_neighbors, odchylenie_neighbors,
			jakosc_czas / 100, odchylenie_jakosc_czas / 100);
	}" $i ;

done;
