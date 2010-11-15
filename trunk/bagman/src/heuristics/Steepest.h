/*
 * Steepest.h
 *
 *  Created on: Nov 9, 2010
 *      Author: piekar294
 */

#ifndef STEEPEST_H_
#define STEEPEST_H_

#include <limits.h>

#include "Calculation.h"
#include "../transformations/Transformation2OPT.h"

class Steepest: public Calculation {
public:
	Steepest(string strSave);
	virtual ~Steepest();
	virtual vector<int> *solve(Generate *pgenData, string ovFileName);
	virtual vector<int> *solve(Generate *pgenData, unsigned int pintMaxIterCount, string ovFileName);
};

#endif /* STEEPEST_H_ */
