#include <iostream>
#include <stdio.h>

#include "solver/TSPLocalSearch.h"
#include "solver/TSPRandomSolver.h"
#include "solver/TSPSteepestSolver.h"
#include "solver/TSPGreedySolver.h"
#include "solver/TSPGreedySolver2.h"

#include "tsp.h"

using namespace std;

int main(int argc, char *argv[])
{
	Instance *instance;
	TSPRandomSolver *randomSolver;
	TSPSteepestSolver *steepestSolver;
	TSPGreedySolver *greedySolver;
	TSPGreedySolver2 *greedySolver2;
	Result *res;
	u_int32_t randomStepsCount = 100000;
	u_int32_t stepsCount = 1000;
	srand(time(NULL));

	instance = Instance::generateRandomInstance(100);
	instance->print();
	printf("\n\n");

	printf("==========ograniczenie dolne dla instancji==============\n");
	printf("%u\n", instance->calculateMinLimit());

	printf("==========wynik dzialania algorytmu losowego==============\n");
	randomSolver = new TSPRandomSolver(instance);
	randomSolver->setStepsCount(randomStepsCount);
	res = randomSolver->solve();
	res->print();
	delete randomSolver;
	delete res;

	printf("==========wynik dzialania algorytmu steepest==============\n");
	steepestSolver = new TSPSteepestSolver(instance);
	steepestSolver->setStepsCount(stepsCount);
	res = steepestSolver->solve();
	res->print();
	delete steepestSolver;
	delete res;

	printf("==========wynik dzialania algorytmu greedy==============\n");
	greedySolver = new TSPGreedySolver(instance, stepsCount);
	res = greedySolver->solve();
	res->print();
	delete greedySolver;
	delete res;

	printf("==========wynik dzialania algorytmu greedy2==============\n");
	greedySolver2 = new TSPGreedySolver2(instance);
	res = greedySolver2->solve();
	res->print();
	delete greedySolver2;
	delete res;

	delete instance;
}
