/*
 * TSPSteepestSolver.h
 *
 *  Created on: 2010-10-28
 *      Author: kolczak
 */

#ifndef TSPSTEEPESTSOLVER_H_
#define TSPSTEEPESTSOLVER_H_

#include "TSPSolver.h"
#include "Timer.h"

class TSPSteepestSolver: public TSPSolver
{
public:
	TSPSteepestSolver(Instance *inst, string output);
	TSPSteepestSolver(u_int32_t, string output);
	void setStepsCount(u_int32_t);
	u_int32_t getStepsCount();
	virtual ~TSPSteepestSolver();

	virtual Result *solve();

protected:
	u_int32_t _stepsCount;
private:
	Result *checkNeighbours(Result*);
};

#endif /* TSPSTEEPESTSOLVER_H_ */
