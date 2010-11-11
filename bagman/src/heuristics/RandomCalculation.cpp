/*
 * RandomCalculation.cpp
 *
 *  Created on: 25-10-2010
 *      Author: qba
 */

#include "RandomCalculation.h"

RandomCalculation::RandomCalculation() {
	// TODO Auto-generated constructor stub

}

RandomCalculation::~RandomCalculation() {
	// TODO Auto-generated destructor stub
}

vector<int> *RandomCalculation::solve(Generate *pgenData) {
	return solve(pgenData, MAX_ROUND);
}

vector<int> *RandomCalculation::solve(Generate *pgenData, int pintMaxIterCount) {
	_iNumberOfCities = pgenData->getNumberOfCities();
	vector<int> *vctrSolution = new vector<int> ();
	vector<int> *vctrBestSolution = NULL;
	int iBestResult = 0;
	int iTmp;
	for (int i = 0; i < _iNumberOfCities; i++) {
		vctrSolution->push_back(i);
	}
	vctrBestSolution = vctrSolution;
	iBestResult = pgenData->calculateWholeDistance(vctrBestSolution);
	for (int i = 0; i < pintMaxIterCount; i++) {
		random_shuffle(vctrSolution->begin(), vctrSolution->end());
		if ((iTmp = pgenData->calculateWholeDistance(vctrSolution)) < iBestResult) {
			iBestResult = iTmp;
			vctrBestSolution = vctrSolution;
		}
	}
	return vctrBestSolution;
}
