/*
 * Own.cpp
 *
 *  Created on: 11-11-2010
 *      Author: qba
 */

#include "Own.h"

Own::Own(string strTimeFileName, string strIterationFileName, string strStepFileName) : Calculation(strTimeFileName, strIterationFileName, strStepFileName) {
	// TODO Auto-generated constructor stub
}

Own::Own(string strFileName) : Calculation(strFileName) {
	// TODO Auto-generated constructor stub
}

Own::Own() {

}

Own::~Own() {
	// TODO Auto-generated destructor stub
}

vector<int> *Own::solve(Generate *pgenData, string fileName) {
	_timer.start();
	string vFileName = fileName + ".vec";
	DataSaver *vSaver = DataSaver::GetIterationFile(vFileName);
	DataSaver *tSaver = DataSaver::GetTimeFile(fileName + ".tm");

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

	tSaver->saveLine(_timer.getRunTime(), pgenData->calculateWholeDistance(vctrSolution));
	vSaver->saveLine(vctrSolution);
	delete vSaver;
	delete tSaver;
	return vctrSolution;
}

vector<int> *Own::solve(Generate *pgenData, int pintMaxIterCount, string fileName) {
	return solve(pgenData, fileName);
}
