/*
 * TSPSimulatedAnnealing.cpp
 *
 *  Created on: 2010-11-26
 *      Author: kolczak
 */

#include "TSPSimulatedAnnealing.h"

TSPSimulatedAnnealing::TSPSimulatedAnnealing(Instance *inst, string output) : TSPSolver(output) {
	_temperature = TEMP;
	TSPSolver::_instance = inst;
	saver = new TSPDataSaver(output.c_str(), inst);
}

TSPSimulatedAnnealing::TSPSimulatedAnnealing(u_int32_t size, string output) : TSPSolver(output) {
	_temperature = TEMP;
	_instance = Instance::generateRandomInstance(size);
	saver = new TSPDataSaver(output.c_str(), _instance);
}

float TSPSimulatedAnnealing::acceptanceProbability(int curDistance, int nextDistance) {
	int up = abs((nextDistance - curDistance));
	//cout << "góra w funkcji akceptacji: " << up << endl;
	//cout << "temperatura: " << _temperature << endl;
	return exp(up/_temperature);
}

Result *TSPSimulatedAnnealing::solve() {
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
	int bestDistance;
	int noBadMovesCounter = 0;
	u_int32_t loopCounter = 0;
	int nextDistance;
	int curDistance;

	cur = generateRandomResult();
	best = new Result(*cur);
	bestDistance = calculateDistance(cur);

	while(
			 ( _temperature > TEMP_MIN ) &&
			 ( loopCounter < getNumberOfSteps() ) &&
			 ( noBadMovesCounter < BAD_MOVES_MAX )
			) {

		next = new Result(*cur);
		next->swapRandomly();

		nextDistance = calculateDistance(next);
		next->setCalculatedDistance(nextDistance);
		curDistance = calculateDistance(cur);
		cur->setCalculatedDistance(curDistance);

		float lotery = ((float)rand()/(float)RAND_MAX);
		float accProb = acceptanceProbability(curDistance, nextDistance);

		//kiedy przechodzimy do nowego rozwiazania
		if ((nextDistance < curDistance) ||
				(lotery > accProb)) {
			delete cur;
			cur = next;
			noBadMovesCounter = 0;

			if (nextDistance < bestDistance) {
				if (best != NULL)
					delete best;
				best = new Result(*next);
				bestDistance = nextDistance;
				best->setCalculatedDistance(bestDistance);
			}
		} else {
			noBadMovesCounter++;
			delete next;
		}
		loopCounter++;
		_temperature *= ALFA;
	}
	return best;
}

TSPSimulatedAnnealing::~TSPSimulatedAnnealing() {
	// TODO Auto-generated destructor stub
}
