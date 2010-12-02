/*
 * Tabu.h
 *
 *  Created on: Nov 30, 2010
 *      Author: piekar294
 */

#ifndef TABU_H_
#define TABU_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "../Generate.h"
#include "../transformations/ChangeMaker.h"
#include "../DataSaver.h"
#include "../utilities/Timer.h"
#include "Calculation.h"
#include "../transformations/Transformation2OPT.h"
#include "TSList.h"

using namespace std;

class Tabu : public Calculation {
public:
	Tabu(unsigned int tabuSize, unsigned int neighSearched, unsigned int iterationsNo);
	virtual ~Tabu();

	virtual vector<int> *solve(Generate *pgenData, string ovFileName);
	virtual vector<int> *solve(Generate *pgenData, unsigned int pintMaxIterCount, string ovFileName);

private:
	inline int distanceFromBest(int best, int current) { return current - best; }
	unsigned int _tabuSize;
	unsigned int _neighSerchPercent;
	unsigned int _iterationsNo;
	int distanceMax;
};

#endif /* TABU_H_ */
