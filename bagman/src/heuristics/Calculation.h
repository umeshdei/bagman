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
	Calculation(string strFileName);
	Calculation();
	~Calculation();
	virtual vector<int> *solve(Generate *pgenData, string ovFileName) = 0;
	virtual vector<int> *solve(Generate *pgenData, unsigned int pintMaxIterCount, string ovFileName) = 0;

protected:
	DataSaver *_ovallSaver;
	Timer _timer;
};

#endif /* CALCULATION_H_ */
