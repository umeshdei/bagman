/*
 * RandomCalculation.h
 *
 *  Created on: 25-10-2010
 *      Author: qba
 */

#ifndef RANDOMCALCULATION_H_
#define RANDOMCALCULATION_H_

#define MAX_ROUND 1000

#include <vector>
#include <time.h>
#include <stdlib.h>

#include "../Generate.h"
#include "Calculation.h"

using namespace std;

class RandomCalculation: public Calculation {
public:
	RandomCalculation();
	virtual ~RandomCalculation();
	vector<int> *solve(Generate *pgenData);
private:
	void shakeIt(vector<int> *vctrData);
	int _iNumberOfCities;
};

#endif /* RANDOMCALCULATION_H_ */
