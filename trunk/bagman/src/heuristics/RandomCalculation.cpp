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
	vector<int> *vctrSolution = pgenData->getRandomResult();
	vector<int> *vctrBestSolution = new vector<int>(*vctrSolution);
	int iBestResult = pgenData->calculateWholeDistance(vctrBestSolution);
	int iTmp;
	for (int i = 0; i < pintMaxIterCount; i++) {
		random_shuffle(vctrSolution->begin(), vctrSolution->end());
		if ((iTmp = pgenData->calculateWholeDistance(vctrSolution)) < iBestResult) {
			iBestResult = iTmp;
			(*vctrBestSolution) = (*vctrSolution);
		}
	}
	return vctrBestSolution;
}