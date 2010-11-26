/*
 * TSPSimulatedAnnealing.h
 *
 *  Created on: 2010-11-26
 *      Author: kolczak
 */

#ifndef TSPSIMULATEDANNEALING_H_
#define TSPSIMULATEDANNEALING_H_

#include "TSPSolver.h"
#include "Result.h"

//TODO: ogarnac te stale
#define TEMP 100000
#define ALFA 0.99
#define TEMP_MIN 1
#define BAD_MOVES_MAX 1000

class TSPSimulatedAnnealing: public TSPSolver {
public:
	TSPSimulatedAnnealing(Instance *inst, string output);
	TSPSimulatedAnnealing(u_int32_t, string output);
	virtual ~TSPSimulatedAnnealing();

	virtual Result *solve();
private:
	float _temperature;

	float acceptanceProbability(int curDistance, int nextDistance);
};

#endif /* TSPSIMULATEDANNEALING_H_ */
