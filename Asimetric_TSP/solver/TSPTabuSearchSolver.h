/*
 * TSPTabuSearchSolver.h
 *
 *  Created on: 2010-11-26
 *      Author: kolczak
 */

#ifndef TSPTABUSEARCHSOLVER_H_
#define TSPTABUSEARCHSOLVER_H_

#include "TSPSolver.h"

class TSPTabuSearchSolver: public TSPSolver {
public:
	TSPTabuSearchSolver(Instance *inst, string output);
	TSPTabuSearchSolver(u_int32_t size, string output);
	virtual ~TSPTabuSearchSolver();
};

#endif /* TSPTABUSEARCHSOLVER_H_ */
