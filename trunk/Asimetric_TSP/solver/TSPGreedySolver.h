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
	TSPGreedySolver();
	virtual ~TSPGreedySolver();

	virtual Result *solve();
};

#endif /* TSPGREEDYSOLVER_H_ */
