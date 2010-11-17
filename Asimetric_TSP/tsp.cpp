#include <stdio.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>

#include <iostream>

#include "Timer.h"

#include "solver/TSPLocalSearch.h"
#include "solver/TSPRandomSolver.h"
#include "solver/TSPSteepestSolver.h"
#include "solver/TSPGreedySolver.h"
#include "solver/TSPGreedySolver2.h"

#include "tsp.h"

#define GREEDY     1 << 1
#define GREEDY2    1 << 2
#define RANDOM     1 << 3
#define STEEPEST   1 << 4

using namespace std;

typedef struct
{
	int solution;
	int max_iterations;
	int size;
	string filename;

} cmd_parameters_t;

Result *run_greedy(Instance *instance, u_int32_t stepsCount)
{
	TSPGreedySolver *greedySolver;
	Result *res;

	greedySolver = new TSPGreedySolver(instance, stepsCount);
	res = greedySolver->solve();
	res->print();
	delete greedySolver;

	return res;
}

Result *run_greedy2(Instance *instance)
{
	TSPGreedySolver2 *greedySolver2;
	Result *res;

	greedySolver2 = new TSPGreedySolver2(instance);
	res = greedySolver2->solve();
	res->print();
	delete greedySolver2;

	return res;
}

Result *run_steepest(Instance *instance, u_int32_t stepsCount)
{
	TSPSteepestSolver *steepestSolver;
	Result *res;

	steepestSolver = new TSPSteepestSolver(instance);
	steepestSolver->setStepsCount(stepsCount);
	res = steepestSolver->solve();
	res->print();
	delete steepestSolver;

	return res;
}

Result *run_random(Instance *instance, u_int32_t randomStepsCount)
{
	TSPRandomSolver *randomSolver;
	Result *res;

	randomSolver = new TSPRandomSolver(instance);
	randomSolver->setStepsCount(randomStepsCount);
	res = randomSolver->solve();
	res->print();
	delete randomSolver;

	return res;
}

void run_heuristics(cmd_parameters_t params)
{
	Instance *instance;
	Result *res;
	Timer timer;

	if (params.size > 0)
		instance = Instance::generateRandomInstance(params.size);
	else
		instance = Instance::generateRandomInstance(0);

	for (int i = 0; i < 10; i++)
	{
		if (params.solution & GREEDY)
		{
			timer.start();
			res = run_greedy(instance, params.max_iterations);
			timer.getRunTime(); // TODO: to zapisac przy, do tego pobrac oczywiscie wynik, neighorsVisited oraz numberOfSteps
			delete res;
		}

		if (params.solution & GREEDY2)
		{
			timer.start();
			res = run_greedy2(instance);
			timer.getRunTime();
			delete res;
		}

		if (params.solution & STEEPEST)
		{
			timer.start();
			res = run_steepest(instance, params.max_iterations);
			timer.getRunTime();
			delete res;
		}

		if (params.solution & RANDOM)
		{
			timer.start();
			res = run_random(instance, params.max_iterations);
			timer.getRunTime();
			delete res;
		}
	}

	//instance->saveToFile("jakis_plik")
	delete instance;
}
void command_line_parameters(int argc, char *argv[])
{
	cmd_parameters_t params;
	Instance *instance;
	bool generate = false;
	int c;

	params.solution = 0;

	while (1) {
		int option_index = 0;
		static struct option long_options[] = {
			{ "help", 0, 0, 0 }, { 0, 0, 0, 0 },
			{ "generate", 0, 0, 0 }, { 0, 0, 0, 0 }
		};

		c = getopt_long(argc, argv, "l:s:i:gteroa:dw", long_options, &option_index);
		if (c == -1)
			break;

		switch (c) {
		case 0:
			if (!strcmp(long_options[option_index].name, "generate"))
				generate = true;
			break;
		case 'g':
			params.solution = params.solution | GREEDY;
			break;
		case 'e':
			params.solution = params.solution | GREEDY2;
			break;
		case 'r':
			params.solution = params.solution | RANDOM;
			break;
		case 't':
			params.solution = params.solution | STEEPEST;
			break;
		case 'a':
			params.solution = params.solution | GREEDY | GREEDY2 | RANDOM | STEEPEST;
		case 'o':
			break;
		case 'l':
			params.filename = string(optarg);
			break;
		case 'p':
			params.size = atoi(optarg);
			break;
		case 'd':
			//DEBUG = true;
			break;
		case 'i':
			params.max_iterations = atoi(optarg);
			break;
		case '?':
		default:
			break;
		}
	}

	if (params.filename.empty())
	{
		if (generate)
		{
			instance = Instance::generateRandomInstance(params.size, time(NULL));
			instance->saveToFile(params.filename);
		}
		else
		{
			instance = Instance::loadFromFile(params.filename);
		}
	}
	else
	{
	}
}

int main(int argc, char *argv[])
{
	Instance *instance;
	string str;
//	Instance *instance;
//	u_int32_t randomStepsCount = 100000;
//	u_int32_t stepsCount = 1000;
//	srand(time(NULL));
//
//	instance = Instance::generateRandomInstance(100);
//	instance->print();
//
//	printf("==========ograniczenie dolne dla instancji==============\n");
//	printf("%u\n", instance->calculateMinLimit());
//
//	delete instance;

	if (argc == 2)
		str = (string)argv[1];
	else
		str = (string)"ALL_atsp/ft53.atsp";

	instance = Instance::loadFromFile(str);
	if (instance == NULL)
	{
		cout << "BLAD! Brak instacji" << endl;
		return 0;
	}
	instance->print();
	return 0;
}
