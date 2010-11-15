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
	Own(string strSave);
	virtual ~Own();
	virtual vector<int> *solve(Generate *pgenData, string ovFileName);
	virtual vector<int> *solve(Generate *pgenData, unsigned int pintMaxIterCount, string ovFileName);
};

#endif /* OWN_H_ */
