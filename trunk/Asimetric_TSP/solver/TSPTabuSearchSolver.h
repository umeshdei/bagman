/*
 * TSPTabuSearchSolver.h
 *
 *  Created on: 2010-11-26
 *      Author: kolczak
 */

#ifndef TSPTABUSEARCHSOLVER_H_
#define TSPTABUSEARCHSOLVER_H_

#include "TSPSolver.h"
#include "Point.h"
#include "TabuList.h"

class TSPTabuSearchSolver: public TSPSolver {
public:
	TSPTabuSearchSolver(Instance *inst, string output);
	TSPTabuSearchSolver(u_int32_t size, string output);
	Result *bestPossibleNeighbour(Result* pure, Result *bestKnown);
	virtual ~TSPTabuSearchSolver();
	virtual Result *solve();
private:
	TabuList *_tabuList;
};

#endif /* TSPTABUSEARCHSOLVER_H_ */
