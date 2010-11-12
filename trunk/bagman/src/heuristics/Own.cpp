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
	vector<int> *vctrSolution = new vector<int>();
	vector<int> *vctrCitiesLeft = pgenData->getSortedResult();

	int iNextCityID = 0;
	vctrSolution->push_back(vctrCitiesLeft->at(iNextCityID));
	vctrCitiesLeft->erase(vctrCitiesLeft->begin());

	while (vctrCitiesLeft->size()) {
		iNextCityID = pgenData->findClosest_returnID(vctrSolution->back(), vctrCitiesLeft);
		vctrSolution->push_back(vctrCitiesLeft->at(iNextCityID));
		vctrCitiesLeft->erase(vctrCitiesLeft->begin() + iNextCityID);
	}
	return vctrSolution;
}

vector<int> *Own::solve(Generate *pgenData, int pintMaxIterCount, string fileName) {
	return solve(pgenData, fileName);
}
