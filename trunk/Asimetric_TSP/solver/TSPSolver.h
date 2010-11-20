/*
 * TSPSolver.h
 *
 *  Created on: 2010-10-26
 *      Author: prog
 */

#ifndef TSPSOLVER_H_
#define TSPSOLVER_H_

#include "io/Instance.h"
#include "io/Result.h"
#include "TSPDataSaver.h"

#include <algorithm>
#include <map>
//#include <glib-2.0/glib.h>

#define FREQUENCY_SAVER	10;

class TSPSolver
{
public:
	TSPSolver(string output);
	virtual ~TSPSolver();

	static void randomizeResult(Result *);
	virtual Result *solve() = 0;

	u_int32_t getNumberOfSteps() { return numberOfSteps; }
//	u_int32_t get

protected:
	Result *generateRandomResult();
	u_int32_t calculateDistance(Result *);
	u_int32_t numberOfSteps;
	string output_filename;

	TSPDataSaver *saver;
	Instance *_instance;
};

#endif /* TSPSOLVER_H_ */
