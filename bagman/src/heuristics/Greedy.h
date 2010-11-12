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
	Greedy(string strTimeFileName, string strIterationFileName, string strStepFileName);
	Greedy(string strFileName);
	Greedy();
	virtual ~Greedy();
	virtual vector<int> *solve(Generate *pgenData, string fileName);
	virtual vector<int> *solve(Generate *pgenData, int pintMaxIterCount, string fileName);
};

#endif /* GREEDY_H_ */
