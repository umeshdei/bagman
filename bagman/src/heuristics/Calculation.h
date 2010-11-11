/*
 * Calculation.h
 *
 *  Created on: 24-10-2010
 *      Author: qba
 */

#ifndef CALCULATION_H_
#define CALCULATION_H_

#include <vector>

#include "../Generate.h"
#include "../utilities/Timer.h"

using namespace std;

class Calculation {
public:
	virtual vector<int> *solve(Generate *pgenData) = 0;
	virtual vector<int> *solve(Generate *pgenData, int pintMaxIterCount) = 0;

protected:
	Timer _timer;
};

#endif /* CALCULATION_H_ */
