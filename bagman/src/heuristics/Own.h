/*
 * Own.h
 *
 *  Created on: 11-11-2010
 *      Author: qba
 */

#ifndef OWN_H_
#define OWN_H_

#include "Calculation.h"

class Own: public Calculation {
public:
	Own(string strTimeFileName, string strIterationFileName, string strStepFileName);
	Own(string strFileName);
	Own();
	virtual ~Own();
	virtual vector<int> *solve(Generate *pgenData, string fileName);
	virtual vector<int> *solve(Generate *pgenData, int pintMaxIterCount, string fileName);
};

#endif /* OWN_H_ */