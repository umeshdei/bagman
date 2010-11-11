/*
 * Own.cpp
 *
 *  Created on: 11-11-2010
 *      Author: qba
 */

#include "Own.h"

Own::Own() {
	// TODO Auto-generated constructor stub

}

Own::~Own() {
	// TODO Auto-generated destructor stub
}

vector<int> *Own::solve(Generate *pgenData) {
	vector<int> *vctrSolution = new vector<int>();
	vector<int> *vctrCitiesLeft = pgenData->getSortedResult();

	int iNextCityID = 0;
	vctrSolution->push_back(vctrCitiesLeft->at(iNextCityID));
	vctrCitiesLeft->erase(vctrCitiesLeft->begin() + iNextCityID);

	while (vctrCitiesLeft->size()) {
		iNextCityID = pgenData->findClosest_returnID(vctrSolution->back(), vctrCitiesLeft);
		vctrSolution->push_back(vctrCitiesLeft->at(iNextCityID));
		vctrCitiesLeft->erase(vctrCitiesLeft->begin() + iNextCityID);
	}
	return vctrSolution;
}

vector<int> *Own::solve(Generate *pgenData, int pintMaxIterCount) {
	return solve(pgenData);
}
