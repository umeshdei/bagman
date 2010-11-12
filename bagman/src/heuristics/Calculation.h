/*
 * Calculation.h
 *
 *  Created on: 24-10-2010
 *      Author: qba
 */

#ifndef CALCULATION_H_
#define CALCULATION_H_

#include <vector>
#include <string>
#include <fstream>

#include "../DataSaver.h"

#include <iostream>

#include "../Generate.h"
#include "../utilities/Timer.h"

using namespace std;

class Calculation {
public:
	Calculation(string strTimeFileName, string strIterationFileName, string strStepFileName);
	Calculation(string strFileName);
	~Calculation();
	virtual vector<int> *solve(Generate *pgenData) = 0;
	virtual vector<int> *solve(Generate *pgenData, int pintMaxIterCount) = 0;

protected:
	DataSaver *_timeSaver;
	DataSaver *_iteretionSaver;
	DataSaver *_stepSaver;
	Timer _timer;
};

#endif /* CALCULATION_H_ */
