/*
 * generate.cpp
 *
 *  Created on: 24-10-2010
 *      Author: qba
 */

#include "Generate.h"

Generate::Generate(int piNumberOfCities) {
	if (piNumberOfCities < 1)
		throw "Illegal parameter in Generate Constructor: piNumberOfCities cannot be less then 1.";
	_iNumberOfCities = piNumberOfCities;
	_iaDistanceBetweenCities = new int*[_iNumberOfCities];
	for (int i = 0; i < _iNumberOfCities; i++) {
		_iaDistanceBetweenCities[i] = new int[_iNumberOfCities];
	}
	generateDistances();
}

Generate::Generate(string psFileName) {
	ifstream strFileName(psFileName.c_str());
	strFileName >> _iNumberOfCities;
	_iaDistanceBetweenCities = new int*[_iNumberOfCities];
	for (int i = 0; i < _iNumberOfCities; i++) {
		_iaDistanceBetweenCities[i] = new int[_iNumberOfCities];
	}
	int tmp;
	for (int i = 1; i < _iNumberOfCities; i++) {
		for (int j = 0; j < i; j++)
		{
			strFileName >> tmp;
			_iaDistanceBetweenCities[i][j] = tmp;
			_iaDistanceBetweenCities[j][i] = tmp;
		}
		_iaDistanceBetweenCities[i][i] = 0;
	}
}

Generate::~Generate() {
	if (_iNumberOfCities > 0) {

		for (int i = 0; i < _iNumberOfCities; i++) {
			delete _iaDistanceBetweenCities[i];
		}
		delete _iaDistanceBetweenCities;
	}
}

void Generate::saveTable(string psFileName) {
	ofstream strFileName(psFileName.c_str(), ios::out);
	strFileName << _iNumberOfCities << endl;
	for (int i = 1; i < _iNumberOfCities; i++) {
		for (int j = 0; j < i; j++)
			strFileName << _iaDistanceBetweenCities[i][j] << " ";
		strFileName << endl;
	}
	strFileName.close();
}

void Generate::generateDistances() {
	srand(time(NULL));
	vector<Point *> *vctrCities = new vector<Point *>();

	for (int i = 0; i < _iNumberOfCities; i++)
		vctrCities->push_back(Point::generateRandomPoint(MAX_VALUE, MAX_VALUE));

	for (int i = 0; i < _iNumberOfCities - 1; i++)
		for (int j = i + 1; j < _iNumberOfCities; j++) {
			_iaDistanceBetweenCities[i][j] = Point::getDistanceBetweenPoints(vctrCities->at(i), vctrCities->at(j));
			_iaDistanceBetweenCities[j][i] = _iaDistanceBetweenCities[i][j];
		}
	for (int i = 0; i < _iNumberOfCities; i++)
		_iaDistanceBetweenCities[i][i] = 0;

	vctrCities->empty();
	delete vctrCities;
}

int Generate::getDistance(int piFirstCityNumber, int piSecondCityNumber) {
	return _iaDistanceBetweenCities[piFirstCityNumber][piSecondCityNumber];
}

int Generate::getNumberOfCities() {
	return _iNumberOfCities;
}

int Generate::calculateWholeDistance(vector<int> *pvCitiesSequence) {
	if (pvCitiesSequence == NULL)
		return -1;
	int iTmpCalculation = 0;
	for (unsigned int i = 0; i < pvCitiesSequence->size(); i++)
		iTmpCalculation += getDistance((*pvCitiesSequence)[i], (*pvCitiesSequence)[(i + 1) % _iNumberOfCities]);
	return iTmpCalculation;
}

vector<int>* Generate::getSortedResult() {
	vector<int> *result = new vector<int>;
	for (int i = 0; i < _iNumberOfCities; i++) {
		result->push_back(i);
	}
	return result;
}

vector<int>* Generate::getRandomResult() {
	vector<int> *result = getSortedResult();
	random_shuffle(result->begin(), result->end());
	return result;
}

int Generate::findClosest(int piCityNumber, vector<int> *pvctrAvailableCities) {
	if (!pvctrAvailableCities->size()) return -1;
	int iResult = (*pvctrAvailableCities)[0];
	int iTmp;
	int iDistance = getDistance(piCityNumber, iResult);
	for (unsigned int i = 1; i < pvctrAvailableCities->size(); i++)
		if ((iTmp = getDistance(piCityNumber, (*pvctrAvailableCities)[i])) < iDistance)
		{
			iResult = (*pvctrAvailableCities)[i];
			iDistance = iTmp;
		}
	return iResult;
}

int Generate::findClosest_returnID(int piCityNumber, vector<int> *pvctrAvailableCities) {
	if (!pvctrAvailableCities->size()) return -1;
	int iResult = 0;
	int iTmp;
	int iDistance = getDistance(piCityNumber, (*pvctrAvailableCities)[iResult]);
	for (unsigned int i = 1; i < pvctrAvailableCities->size(); i++)
		if ((iTmp = getDistance(piCityNumber, (*pvctrAvailableCities)[i])) < iDistance)
		{
			iResult = i;
			iDistance = iTmp;
		}
	return iResult;
}


void Generate::DEBUG_printTrace(vector <int> *pvCitiesSequence) {
	cout << "  " << pvCitiesSequence->front();
	for (unsigned int i = 1; i < pvCitiesSequence->size(); i++)
		cout << " --(" << getDistance((*pvCitiesSequence)[i - 1], (*pvCitiesSequence)[i]) << ")--> " << (*pvCitiesSequence)[i];
	cout << " --(" << getDistance(pvCitiesSequence->front(), pvCitiesSequence->back()) << ")--> " << pvCitiesSequence->front();
	cout << endl;
}
