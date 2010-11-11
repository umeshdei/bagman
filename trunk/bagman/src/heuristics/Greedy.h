/*
 * Greedy.h
 *
 *  Created on: Nov 6, 2010
 *      Author: piekar294
 */

#ifndef GREEDY_H_
#define GREEDY_H_

#include <limits.h>

#include "Calculation.h"
#include "../transformations/Transformation2OPT.h"

class Greedy: public Calculation {
public:
	Greedy(string strOutputFileName);
	virtual ~Greedy();
	virtual vector<int> *solve(Generate *pgenData);
	virtual vector<int> *solve(Generate *pgenData, int pintMaxIterCount);
};

#endif /* GREEDY_H_ */
