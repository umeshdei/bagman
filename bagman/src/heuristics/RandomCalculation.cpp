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

void RandomCalculation::shakeIt(vector<int> *vctrData) {
	int iTmp = 0;
	int iData = 0;
	vector<int>::iterator iter = vctrData->begin();
	vector<int>::iterator iter1;
	for (int i = 0; i < MAX_ROUND; i++) {
		iTmp = rand() % vctrData->size();
		iter1 = iter + iTmp;
		iData = vctrData->at(iTmp);
		vctrData->erase(iter1);

		iTmp = rand() % vctrData->size();
		iter1 = iter + iTmp;
		vctrData->insert(iter1, iData);
	}
}

vector<int> *RandomCalculation::solve(Generate *pgenData) {
	_iNumberOfCities = pgenData->getNumberOfCities();
	vector<int> *vctrSolution = new vector<int> ();
	vector<int> *vctrBectSolution = NULL;
	int iBestResult = 0;
	int iTmp;
	for (int i = 0; i < _iNumberOfCities; i++) {
		vctrSolution->push_back(i);
	}
	vctrBectSolution = vctrSolution;
	iBestResult = pgenData->calculateWholeDistance(vctrBectSolution);
	for (int i = 0; i < MAX_ROUND; i++) {
		shakeIt(vctrSolution);
		if ((iTmp = pgenData->calculateWholeDistance(vctrSolution)) < iBestResult) {
			iBestResult = iTmp;
			vctrBectSolution->clear();
			delete vctrBectSolution;
			vctrBectSolution = vctrSolution;
		}
	}
	return vctrBectSolution;
}
