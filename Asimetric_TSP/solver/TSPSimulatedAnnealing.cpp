/*
 * TSPSimulatedAnnealing.cpp
 *
 *  Created on: 2010-11-26
 *      Author: kolczak
 */

#include "TSPSimulatedAnnealing.h"
#include "TSPGreedySolver2.h"

TSPSimulatedAnnealing::TSPSimulatedAnnealing(Instance *inst, string output) : TSPSolver(output)
{
	_startTemperature = DEFAULT_TEMP;
	_endTemperature = DEFAULT_TEMP_MIN;
	_alpha = DEFAULT_ALFA;
	_maxBadMoves = DEFAULT_BAD_MOVES_MAX;
	_temperature = DEFAULT_TEMP;
	TSPSolver::_instance = inst;
	saver = new TSPDataSaver(output.c_str(), inst);
}

TSPSimulatedAnnealing::TSPSimulatedAnnealing(u_int32_t size, string output) : TSPSolver(output)
{
	_startTemperature = DEFAULT_TEMP;
	_endTemperature = DEFAULT_TEMP_MIN;
	_alpha = DEFAULT_ALFA;
	_maxBadMoves = DEFAULT_BAD_MOVES_MAX;
	_temperature = DEFAULT_TEMP;
	_instance = Instance::generateRandomInstance(size);
	saver = new TSPDataSaver(output.c_str(), _instance);
}

float TSPSimulatedAnnealing::acceptanceProbability(int curDistance, int nextDistance)
{
	int up = abs(nextDistance - curDistance);
	return exp(-(double)up / _temperature);
}

Result *TSPSimulatedAnnealing::solve()
{
	/**
	 * 1). losujesz rozwiazanie
	 * 2). losujesz sąsiada żeby do niego przejść
	 * 3). przechodzisz jak jest lepszy a jak nie to sprawdzasz prawdopodobieństwo przejścia
	 * 4). koniec algorytmu, gdy:
	 * 		- osiągnie daną liczbę kroków
	 * 		- jeżeli nie ma poprawy po określonej liczbie kroków
	 * 		- przy przejśiu sprawdzamy czy temperatuda nie opadła poniżej minimum
	 */
	Result *cur;
	Result *next;
	Result *best = NULL;
	u_int32_t bestDistance = 0, noBadMovesCounter = 0;
	u_int32_t loopCounter = 0;
	u_int32_t neighorsVisited = 0, betterSolutionsCount = 0;
	u_int32_t nextDistance, curDistance, worseSolutions = 0;

	//printf("%f %f %f %d\n", _startTemperature, _endTemperature, _alpha, _maxBadMoves);

	_temperature = _startTemperature;


	cur = generateRandomResult();

//	TSPGreedySolver2 *greedySolver2;
//	greedySolver2 = new TSPGreedySolver2(_instance, "");
//	cur = greedySolver2->solve();
//	delete greedySolver2;

	best = new Result(*cur);
	bestDistance = calculateDistance(cur);

	while ((_temperature > _endTemperature) &&
			(loopCounter < getNumberOfSteps()) && (noBadMovesCounter < _maxBadMoves))
	{
		next = new Result(*cur);
		next->swapRandomly();

		nextDistance = calculateDistance(next);
		next->setCalculatedDistance(nextDistance);
		neighorsVisited++;

		float lotery = ((float) (rand() % RAND_MAX) / (float) RAND_MAX);
		float accProb = acceptanceProbability(curDistance, nextDistance);

		//kiedy przechodzimy do nowego rozwiazania
		if ((nextDistance < curDistance) || (lotery > accProb))
		{
			delete cur;
			cur = next;
			noBadMovesCounter = 0;

			if (nextDistance >= curDistance)
			{
				//printf("worse %f %f %f\n", lotery, accProb, _temperature);
				worseSolutions++;
			}

			if (nextDistance < bestDistance)
			{
				if (best != NULL)
					delete best;
				betterSolutionsCount++;
				best = new Result(*next);
				bestDistance = nextDistance;
				best->setCalculatedDistance(bestDistance);
			}

			curDistance = calculateDistance(cur);
			cur->setCalculatedDistance(curDistance);
		}
		else
		{
			noBadMovesCounter++;
			delete next;
		}
		loopCounter++;
		_temperature *= _alpha;
	}

//	printf("worse: %d\n", worseSolutions);
//	printf("temperature: %f\n", _temperature);
//	printf("loopCounter: %d\n", loopCounter);
//	printf("bad moves: %d\n", noBadMovesCounter);

	best->setNeighborsVisited(neighorsVisited);
	best->setStepsCount(loopCounter);
	best->setBetterSolutionsCount(betterSolutionsCount);

	return best;
}

TSPSimulatedAnnealing::~TSPSimulatedAnnealing()
{
	// TODO Auto-generated destructor stub
}
