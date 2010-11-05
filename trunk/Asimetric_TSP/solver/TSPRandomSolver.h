/*
 * TSPRandomSolver.h
 *
 *  Created on: 2010-10-27
 *      Author: prog
 */

#ifndef TSPRANDOMSOLVER_H_
#define TSPRANDOMSOLVER_H_

#include <stdlib.h>
#include "TSPSolver.h"

class TSPRandomSolver : public TSPSolver
{
public:
	TSPRandomSolver(Instance *inst);
	TSPRandomSolver(u_int32_t);
	void setStepsCount(u_int32_t);
	u_int32_t getStepsCount();
	virtual ~TSPRandomSolver();

	virtual Result *solve();

protected:
	u_int32_t _stepsCount;
};

#endif /* TSPRANDOMSOLVER_H_ */
