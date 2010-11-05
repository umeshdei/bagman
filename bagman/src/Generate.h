/*
 * generate.h
 *
 *  Created on: 24-10-2010
 *      Author: qba
 */

#ifndef GENERATE_H_
#define GENERATE_H_

#include <vector>
#include <string>
#include <fstream>
#include <time.h>
#include <stdlib.h>
#include <algorithm>

#include "Point.h"

#define MAX_VALUE 100

using namespace std;

class Generate {
public:
	Generate(int piNumberOfCities);
	Generate(string psFileName);
	virtual ~Generate();
	int getDistance(int piFirstCityNumber, int piSecondCityNumber);
	int calculateWholeDistance(vector <int> *pvCitiesSequence);
	void saveTable(string psFileName);
	int getNumberOfCities();
	vector<int>* getRandomResult();
private:
	void generateDistances();
	int _iNumberOfCities;
	int **_iaDistanceBetweenCities;
};

#endif /* GENERATE_H_ */
