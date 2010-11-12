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
	virtual ~Own();
	virtual vector<int> *solve(Generate *pgenData);
	virtual vector<int> *solve(Generate *pgenData, int pintMaxIterCount);
};

#endif /* OWN_H_ */
