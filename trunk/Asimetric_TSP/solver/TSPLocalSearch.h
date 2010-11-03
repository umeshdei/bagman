/*
 * TSPLocalSearch.h
 *
 *  Created on: 2010-10-26
 *      Author: prog
 */

#ifndef TSPLOCALSEARCH_H_
#define TSPLOCALSEARCH_H_

#include "TSPSolver.h"

class TSPLocalSearch : public TSPSolver
{
public:
	TSPLocalSearch();
	virtual ~TSPLocalSearch();

	virtual Result *solve();
};

#endif /* TSPLOCALSEARCH_H_ */
