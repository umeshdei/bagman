/*
 * TSPSimpleHeuristicSolver.h
 *
 *  Created on: 2010-11-07
 *      Author: prog
 */

#ifndef TSPSIMPLEHEURISTICSOLVER_H_
#define TSPSIMPLEHEURISTICSOLVER_H_

#include "TSPSolver.h"

#include <list>

using namespace std;

typedef struct
{
	u_int32_t node1_num;
	u_int32_t node2_num;
} change_t;

class TSPSimpleHeuristicSolver: public TSPSolver
{
public:
	TSPSimpleHeuristicSolver();
	Result *solve();
	virtual ~TSPSimpleHeuristicSolver();

private:
	list<change_t> lastChangesList;
};

#endif /* TSPSIMPLEHEURISTICSOLVER_H_ */
