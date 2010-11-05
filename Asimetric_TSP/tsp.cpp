#include <iostream>
#include <stdio.h>

#include "solver/TSPLocalSearch.h"
#include "solver/TSPRandomSolver.h"

#include "tsp.h"

using namespace std;

int main(int argc, char *argv[])
{
	Instance *instance;
	TSPRandomSolver *randomSolver;
	srand(time(NULL));

	instance = Instance::generateRandomInstance(100);
	instance->print();
	printf("\n\n");

	randomSolver = new TSPRandomSolver(instance);
	randomSolver->setStepsCount(10000);
	randomSolver->solve();

}
