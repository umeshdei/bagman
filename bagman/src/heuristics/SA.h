/*
 * SA.h
 *
 *  Created on: Nov 19, 2010
 *      Author: piekar294
 */

#ifndef SA_H_
#define SA_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../Generate.h"
#include "../transformations/Transformation2OPT.h"

class SA {
public:
	SA();
	virtual ~SA();

	//cRate = cooling rating
	vector<int> *solve(Generate *pgenData, string ovFileName, double maxT, double cRate);

private:
	//returns random number between <0;1>.
	static double nextDouble();
};

#endif /* SA_H_ */
