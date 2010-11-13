/*
 * TSPGreedySolver2.h
 *
 *  Created on: 2010-11-06
 *      Author: prog
 */

#ifndef TSPGREEDYSOLVER2_H_
#define TSPGREEDYSOLVER2_H_

#include "TSPSolver.h"
#include "Result.h"
#include "Instance.h"

#include <set>

using namespace std;

class TSPGreedySolver2: public TSPSolver
{
public:
	TSPGreedySolver2(Instance *instance);
	Result *solve();
	virtual ~TSPGreedySolver2();
};

#endif /* TSPGREEDYSOLVER2_H_ */
