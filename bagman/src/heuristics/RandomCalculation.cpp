/*
 * RandomCalculation.cpp
 *
 *  Created on: 25-10-2010
 *      Author: qba
 */

#include "RandomCalculation.h"

RandomCalculation::RandomCalculation(string strSave) : Calculation(strSave) {
	// TODO Auto-generated destructor stub
}

RandomCalculation::~RandomCalculation() {
	// TODO Auto-generated destructor stub
}

vector<int> *RandomCalculation::solve(Generate *pgenData, string ovFileName) {
	return solve(pgenData, MAX_ROUND, ovFileName);
}

vector<int> *RandomCalculation::solve(Generate *pgenData, unsigned int pintMaxIterCount, string ovFileName) {
	_timer.start();

	DataSaver *vSaver = DataSaver::GetIterationFile(ovFileName + ".vec");

	vector<int> *vctrSolution = pgenData->getRandomResult();
	vector<int> *vctrBestSolution = new vector<int>(*vctrSolution);
	int iBestResult = pgenData->calculateWholeDistance(vctrBestSolution);
	int iTmp;

	//save initial values
	_ovallSaver->saveOverallLine(ovFileName, _timer.getRunTime(), 0, 0, iBestResult);


	for (unsigned int i = 0; i < pintMaxIterCount; i++) {
		random_shuffle(vctrSolution->begin(), vctrSolution->end());
		if ((iTmp = pgenData->calculateWholeDistance(vctrSolution)) < iBestResult) {
			iBestResult = iTmp;
			(*vctrBestSolution) = (*vctrSolution);
			//save current score
			_ovallSaver->saveOverallLine(ovFileName, _timer.getRunTime(), i+1, i+1, iBestResult);
		}
	}
	vSaver->saveLine("random", vctrBestSolution);
	delete vSaver;
	return vctrBestSolution;
}
