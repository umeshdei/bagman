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
	TSPTabuSearchSolver(Instance *inst, string output, u_int32_t tabuListSize);
	TSPTabuSearchSolver(u_int32_t size, string output, u_int32_t tabuListSize);
	Result *bestPossibleNeighbour(Result* pure, Result **bestKnown);
	virtual ~TSPTabuSearchSolver();
	virtual Result *solve();

	void setMaxBadMoves(u_int32_t maxBadMoves) { _maxBadMoves = maxBadMoves; }

private:
	u_int32_t neighorsVisited;
	u_int32_t betterSolutionsCount;
	u_int32_t _maxBadMoves;
	u_int32_t _badMoves;
	TabuList *_tabuList;
};

#endif /* TSPTABUSEARCHSOLVER_H_ */
