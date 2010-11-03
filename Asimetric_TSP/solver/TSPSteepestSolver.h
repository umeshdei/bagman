/*
 * TSPSteepestSolver.h
 *
 *  Created on: 2010-10-28
 *      Author: prog
 */

#ifndef TSPSTEEPESTSOLVER_H_
#define TSPSTEEPESTSOLVER_H_

#include "TSPSolver.h"

class TSPSteepestSolver: public TSPSolver
{
public:
	TSPSteepestSolver();
	virtual ~TSPSteepestSolver();

	virtual Result *solve();
};

#endif /* TSPSTEEPESTSOLVER_H_ */
