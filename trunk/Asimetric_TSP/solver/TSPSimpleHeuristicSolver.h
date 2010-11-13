/*
 * TSPSimpleHeuristicSolver.h
 *
 *  Created on: 2010-11-07
 *      Author: prog
 */

#ifndef TSPSIMPLEHEURISTICSOLVER_H_
#define TSPSIMPLEHEURISTICSOLVER_H_

#include "TSPSolver.h"

class TSPSimpleHeuristicSolver: public TSPSolver
{
public:
	TSPSimpleHeuristicSolver();
	Result *solve();
	virtual ~TSPSimpleHeuristicSolver();
};

#endif /* TSPSIMPLEHEURISTICSOLVER_H_ */
