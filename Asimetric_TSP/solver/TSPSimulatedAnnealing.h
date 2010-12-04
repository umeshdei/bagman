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
#define DEFAULT_TEMP 1000000
#define DEFAULT_ALFA 0.9999
#define DEFAULT_TEMP_MIN 0.00001
#define DEFAULT_BAD_MOVES_MAX 300000

class TSPSimulatedAnnealing: public TSPSolver {
public:
	TSPSimulatedAnnealing(Instance *inst, string output);
	TSPSimulatedAnnealing(u_int32_t, string output);
	virtual ~TSPSimulatedAnnealing();

	void setStartTemperature(double startTemperature) { _startTemperature = startTemperature; }
	void setEndTemperature(double endTemperature) { _endTemperature = endTemperature; }
	void setAlpha(double alpha) { _alpha = alpha; }
	void setMaxBadMoves(int maxBadMoves) { _maxBadMoves = maxBadMoves; }

	virtual Result *solve();
private:
	float _temperature;
	double _startTemperature;
	double _endTemperature;
	double _alpha;
	u_int32_t _maxBadMoves;

	float acceptanceProbability(int curDistance, int nextDistance);
};

#endif /* TSPSIMULATEDANNEALING_H_ */
