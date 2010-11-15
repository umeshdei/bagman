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
	RandomCalculation(string strSave);
	virtual ~RandomCalculation();
	vector<int> *solve(Generate *pgenData, string ovFileName);
	vector<int> *solve(Generate *pgenData, unsigned int pintMaxIterCount, string ovFileName);
private:
	int _iNumberOfCities;
};

#endif /* RANDOMCALCULATION_H_ */
