/*
 * TSPSolver.h
 *
 *  Created on: 2010-10-26
 *      Author: prog
 */

#ifndef TSPSOLVER_H_
#define TSPSOLVER_H_

#include "io/Instance.h"
#include "io/Result.h"
#include <algorithm>

class TSPSolver
{
public:
	TSPSolver();
	virtual ~TSPSolver();

	static void randomizeResult(Result *);
	virtual Result *solve() = 0;

protected:
	Result *generateRandomResult();
	u_int32_t calculateDistance(Result *);

	Instance *_instance;
};

#endif /* TSPSOLVER_H_ */
