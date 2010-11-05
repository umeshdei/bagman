#include <iostream>
#include <stdio.h>

#include "solver/TSPLocalSearch.h"
#include "solver/TSPRandomSolver.h"
#include "solver/TSPSteepestSolver.h"

#include "tsp.h"

using namespace std;

int main(int argc, char *argv[])
{
	Instance *instance;
	TSPRandomSolver *randomSolver;
	TSPSteepestSolver *steepestSolver;
	Result *res;
	srand(time(NULL));

	instance = Instance::generateRandomInstance(100);
	instance->print();
	printf("\n\n");


	randomSolver = new TSPRandomSolver(instance);
	randomSolver->setStepsCount(10000);
	res = randomSolver->solve();
	printf("==========wynik dzialania algorytmu randomowego==============\n");
	res->print();


	steepestSolver = new TSPSteepestSolver(instance);
	steepestSolver->setStepsCount(10000);
	res = steepestSolver->solve();
	printf("==========wynik dzialania algorytmu steepest==============\n");
	res->print();
}
