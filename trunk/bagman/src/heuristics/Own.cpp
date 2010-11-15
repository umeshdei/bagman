/*
 * Own.cpp
 *
 *  Created on: 11-11-2010
 *      Author: qba
 */

#include "Own.h"

Own::Own(string strSave) : Calculation(strSave) {
	// TODO Auto-generated constructor stub
}

Own::~Own() {
	// TODO Auto-generated destructor stub
}

vector<int> *Own::solve(Generate *pgenData, string ovFileName) {
	_timer.start();
	DataSaver *vSaver = DataSaver::GetIterationFile(ovFileName + ".vec");

	vector<int> *vctrSolution = new vector<int>();
	vector<int> *vctrCitiesLeft = pgenData->getSortedResult();

	int iNextCityID = random() % pgenData->getNumberOfCities();
	vctrSolution->push_back(vctrCitiesLeft->at(iNextCityID));
	vctrCitiesLeft->erase(vctrCitiesLeft->begin() + iNextCityID);

	while (vctrCitiesLeft->size()) {
		iNextCityID = pgenData->findClosest_returnID(vctrSolution->back(), vctrCitiesLeft);
		vctrSolution->push_back(vctrCitiesLeft->at(iNextCityID));
		vctrCitiesLeft->erase(vctrCitiesLeft->begin() + iNextCityID);
	}

	_ovallSaver->saveOverallLine(ovFileName, _timer.getRunTime(), vctrSolution->size(), vctrSolution->size(), pgenData->calculateWholeDistance(vctrSolution));

	vSaver->saveLine("own", vctrSolution);
	delete vSaver;

	return vctrSolution;
}

vector<int> *Own::solve(Generate *pgenData, unsigned int pintMaxIterCount, string ovFileName) {
	return solve(pgenData, ovFileName);
}
