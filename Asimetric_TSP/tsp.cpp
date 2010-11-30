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
#include "solver/TSPSimulatedAnnealing.h"
#include "solver/TSPTabuSearchSolver.h"

#include "tsp.h"

#define GREEDY     1 << 1
#define GREEDY2    1 << 2
#define RANDOM     1 << 3
#define STEEPEST   1 << 4
#define SIMULATED_ANNEALING 1 << 5
#define TABU_SEARCH 1 << 6

using namespace std;

typedef struct cmd_parameters_t_
{
	int solution;
	int max_iterations;
	int size;
	string filename;
	string output_filename;
	Instance *instance;
	bool tspLib;

	cmd_parameters_t_()
	{
		tspLib = false;
		solution = 0;
		max_iterations = 1000;
		size = 100;
		filename = string("");
		output_filename = string("output");
		instance = NULL;
	}
} cmd_parameters_t;

Result *run_greedy(Instance *instance, u_int32_t stepsCount, string &output)
{
	TSPGreedySolver *greedySolver;
	Result *res;
	Timer timer;

//	cout << "GREEDY" << endl;
	greedySolver = new TSPGreedySolver(instance, stepsCount, output);
	timer.start();
	res = greedySolver->solve();
	printf("%f %d %d %d %d %d\n", timer.getRunTime(), res->getCalculatedDistance(),
			instance->calculateMinLimit(), res->getBetterSolutionsCount(), res->getStepsCount(),
			res->getNeighborsVisited());
	//res->print();
	delete greedySolver;

	return res;
}

Result *run_greedy2(Instance *instance, string &output)
{
	TSPGreedySolver2 *greedySolver2;
	Result *res;
	Timer timer;

//	cout << "GREEDY2" << endl;
	greedySolver2 = new TSPGreedySolver2(instance, output);
	timer.start();
	res = greedySolver2->solve();
	printf("%f %d %d\n", timer.getRunTime(), res->getCalculatedDistance(),
			instance->calculateMinLimit());
	//res->print();
	delete greedySolver2;

	return res;
}

Result *run_steepest(Instance *instance, u_int32_t stepsCount, string &output)
{
	TSPSteepestSolver *steepestSolver;
	Result *res;
	Timer timer;

	//cout << "STEEPEST" << endl;

	steepestSolver = new TSPSteepestSolver(instance, output);
	steepestSolver->setStepsCount(stepsCount);
	timer.start();
	res = steepestSolver->solve();
	printf("%f %d %d %d %d %d\n", timer.getRunTime(), res->getCalculatedDistance(),
			instance->calculateMinLimit(), res->getBetterSolutionsCount(), res->getStepsCount(),
			res->getNeighborsVisited());
	//res->print();
	delete steepestSolver;

	return res;
}

Result *run_random(Instance *instance, u_int32_t randomStepsCount, string &output)
{
	TSPRandomSolver *randomSolver;
	Result *res;
	Timer timer;

//	cout << "RANDOM" << endl;

	randomSolver = new TSPRandomSolver(instance, output);
	randomSolver->setStepsCount(randomStepsCount);
	timer.start();
	res = randomSolver->solve();
	printf("%f %d %d %d %d\n", timer.getRunTime(), res->getCalculatedDistance(),
			instance->calculateMinLimit(), res->getBetterSolutionsCount(), res->getStepsCount());
	//res->print();
	delete randomSolver;

	return res;
}

Result *run_simulated_annealing(Instance *instance, u_int32_t stepsCount, string &output)
{
	TSPSimulatedAnnealing *saSolver;
	Result *res;
	Timer timer;

//	cout << "SIMULATED_ANNEALING" << endl;

	saSolver = new TSPSimulatedAnnealing(instance, output);
	saSolver->setNumberOfSteps(stepsCount);
	timer.start();
	res = saSolver->solve();
	printf("%f %d %d %d %d %d\n", timer.getRunTime(), res->getCalculatedDistance(),
			instance->calculateMinLimit(), res->getBetterSolutionsCount(), res->getStepsCount(),
			res->getNeighborsVisited());
	//res->print();
	delete saSolver;

	return res;
}

Result *run_tabu_search(Instance *instance, u_int32_t stepsCount, string &output)
{
	TSPTabuSearchSolver *tsSolver;
	Result *res;
	Timer timer;

//	cout << "TABU_SEARCH" << endl;

	tsSolver = new TSPTabuSearchSolver(instance, output);
	tsSolver->setNumberOfSteps(stepsCount);
	timer.start();
	res = tsSolver->solve();
	printf("%f %d %d %d %d %d\n", timer.getRunTime(), res->getCalculatedDistance(),
			instance->calculateMinLimit(), res->getBetterSolutionsCount(), res->getStepsCount(),
			res->getNeighborsVisited());
	//res->print();
	delete tsSolver;

	return res;
}

void run_heuristics(cmd_parameters_t params)
{
	Instance *instance;
	Result *res;

	if (params.instance == NULL)
	{
		if (!params.filename.empty())
		{
			if (params.tspLib)
				instance = Instance::loadFromFileTSPLib(params.filename);
			else
				instance = Instance::loadFromFile(params.filename);
		}
		else
		{
			if (params.size > 0)
				instance = Instance::generateRandomInstance(params.size);
			else
				instance = Instance::generateRandomInstance(0);
		}
	}
	else
	{
		instance = params.instance;
	}

	for (int i = 0; i < 10; i++)
	{
		if (params.solution & GREEDY)
		{
			res = run_greedy(instance, params.max_iterations, params.output_filename);
			delete res;
		}

		if (params.solution & GREEDY2)
		{
			res = run_greedy2(instance, params.output_filename);
			delete res;
		}

		if (params.solution & STEEPEST)
		{
			res = run_steepest(instance, params.max_iterations, params.output_filename);
			delete res;
		}

		if (params.solution & RANDOM)
		{
			res = run_random(instance, params.max_iterations, params.output_filename);
			delete res;
		}
		if (params.solution & SIMULATED_ANNEALING)
		{
			res = run_simulated_annealing(instance, params.max_iterations, params.output_filename);
		}
		if (params.solution & TABU_SEARCH)
		{
			res = run_tabu_search(instance, params.max_iterations, params.output_filename);
		}
	}

	//instance->saveToFile("jakis_plik")
	delete instance;
}

void command_line_parameters(int argc, char *argv[])
{
	cmd_parameters_t params;
	Instance *instance = NULL;
	bool generate = false;
	int c;

	if (argc < 2)
	{
		printf("give me some parameters\n");
		exit(-1);
	}

	params.solution = 0;

	while (1) {
		int option_index = 0;
		static struct option long_options[] = {
			{ "help", 0, 0, 0 },
			{ "generate", 0, 0, 0 },
			{ "tsp", 0, 0, 0 },
			{ 0, 0, 0, 0 },
		};

		c = getopt_long(argc, argv, "l:o:s:i:bmgteradw", long_options, &option_index);
		if (c == -1)
			break;

		switch (c) {
		case 0:
			if (strcmp(long_options[option_index].name, "generate") == 0)
				generate = true;
			else if (strcmp(long_options[option_index].name, "tsp") == 0)
				params.tspLib = true;
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
		case 'm':
			params.solution = params.solution | SIMULATED_ANNEALING;
			break;
		case 'b':
			params.solution = params.solution | TABU_SEARCH;
			break;
		case 'a':
			params.solution = params.solution | GREEDY | GREEDY2 | RANDOM | STEEPEST;
		case 'o':
			params.output_filename = string(optarg);
			break;
		case 'l':
			params.filename = string(optarg);
			break;
		case 's':
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

	srand(time(NULL) + params.size);
	if (generate && !params.output_filename.empty())
	{
		instance = Instance::generateRandomInstance(params.size, time(NULL));
		instance->saveToFile(params.output_filename);
		exit(0);
	}

	if (!params.filename.empty())
	{
/*
		instance = Instance::loadFromFile(params.filename);
		if (instance)
			instance->setName(params.filename);
		else
		{
			printf("Instance is null. Aborting...\n");
			abort();
		}
*/
		instance = NULL;
	}
	else
	{
		instance = Instance::generateRandomInstance(params.size, time(NULL));
		instance->setName("random");
	}

	params.instance = instance;
	run_heuristics(params);
}

int main(int argc, char *argv[])
{
	command_line_parameters(argc, argv);
//	Instance *instance;
//	string str;
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

	/*
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
	*/
	return 0;
}
