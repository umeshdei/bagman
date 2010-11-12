/*
 * RandomCalculation.h
 *
 *  Created on: 25-10-2010
 *      Author: qba
 */

#ifndef RANDOMCALCULATION_H_
#define RANDOMCALCULATION_H_

#include <vector>
#include <time.h>
#include <stdlib.h>
#include <limits.h>

#include "../Generate.h"
#include "Calculation.h"

#define MAX_ROUND 10000

using namespace std;

class RandomCalculation: public Calculation {
public:
	RandomCalculation(string strTimeFileName, string strIterationFileName, string strStepFileName);
	RandomCalculation(string strFileName);
	RandomCalculation();
	virtual ~RandomCalculation();
	vector<int> *solve(Generate *pgenData, string fileName);
	vector<int> *solve(Generate *pgenData, int pintMaxIterCount, string fileName);
private:
	int _iNumberOfCities;
};

#endif /* RANDOMCALCULATION_H_ */
