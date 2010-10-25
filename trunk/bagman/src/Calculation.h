/*
 * Calculation.h
 *
 *  Created on: 24-10-2010
 *      Author: qba
 */

#ifndef CALCULATION_H_
#define CALCULATION_H_

#include <vector>

#include "Generate.h"

using namespace std;

class Calculation {
public:
	Calculation();
	virtual ~Calculation();
	virtual vector<int> *solve(Generate *pgenData);
};

#endif /* CALCULATION_H_ */
