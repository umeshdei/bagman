/*
 * Steepest.h
 *
 *  Created on: Nov 9, 2010
 *      Author: piekar294
 */

#ifndef STEEPEST_H_
#define STEEPEST_H_

#include "Calculation.h"
#include "../transformations/Transformation2OPT.h"

class Steepest: public Calculation {
public:
	Steepest();
	virtual ~Steepest();
	virtual vector<int> *solve(Generate *pgenData);
	virtual vector<int> *solve(Generate *pgenData, int pintMaxIterCount);
};

#endif /* STEEPEST_H_ */
