/*
 * TSPGreedySolver.h
 *
 *  Created on: 2010-10-28
 *      Author: prog
 */

#ifndef TSPGREEDYSOLVER_H_
#define TSPGREEDYSOLVER_H_

#include "TSPSolver.h"

class TSPGreedySolver: public TSPSolver
{
public:
	TSPGreedySolver(Instance *instance, u_int32_t stepsCount = 100);
	TSPGreedySolver(u_int32_t instanceSize, u_int32_t stepsCount = 100);
	virtual ~TSPGreedySolver();
	void setStepsCount(u_int32_t steps) { _stepsCount = steps; }
	u_int32_t getStepsCount() { return _stepsCount; }
	virtual Result *solve();

private:
	u_int32_t _stepsCount;
};

#endif /* TSPGREEDYSOLVER_H_ */
