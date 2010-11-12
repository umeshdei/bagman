/*
 * RandomCalculation.cpp
 *
 *  Created on: 25-10-2010
 *      Author: qba
 */

#include "RandomCalculation.h"

RandomCalculation::RandomCalculation(string strTimeFileName, string strIterationFileName, string strStepFileName) : Calculation(strTimeFileName, strIterationFileName, strStepFileName) {
	// TODO Auto-generated constructor stub
}

RandomCalculation::RandomCalculation(string strFileName) : Calculation(strFileName) {
	// TODO Auto-generated constructor stub
}

RandomCalculation::RandomCalculation() {
	// TODO Auto-generated destructor stub
}

RandomCalculation::~RandomCalculation() {
	// TODO Auto-generated destructor stub
}

vector<int> *RandomCalculation::solve(Generate *pgenData, string fileName) {
	return solve(pgenData, MAX_ROUND, fileName);
}

vector<int> *RandomCalculation::solve(Generate *pgenData, int pintMaxIterCount, string fileName) {
	_timer.start();
	vector<int> *vctrSolution = pgenData->getSortedResult();
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
