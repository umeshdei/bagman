/*
 * SA.cpp
 *
 *  Created on: Nov 19, 2010
 *      Author: piekar294
 */

#include "SA.h"
#include "string.h"
SA::SA() {
	// TODO Auto-generated constructor stub

}

SA::~SA() {
	// TODO Auto-generated destructor stub
}

bool cmp_vector(vector<int> *p, vector<int> *q) {
	for (unsigned int i = 0; i < p->size(); i++) {
		if (p[i] != q[i])
			return false;
	}
	return true;
}

void printvector(vector<int> *p) {
	for (vector<int>::iterator it = p->begin(); it != p->end(); it++)
		cout <<"["<<*it<<"]";
	cout <<endl;
}

vector<int> *SA::solve(Generate *pgenData, string ovFileName, double maxT, double cRate, string strSave) {
	vector<int> *res = pgenData->getRandomResult();
	vector<int> *best = new vector<int>(*res);
	vector<int> *nextOrder;
	int distance = pgenData->calculateWholeDistance(res);
	DataSaver itSaver(ovFileName + ".sa.vec");
	DataSaver tmSaver(ovFileName + ".sa.tm");
	DataSaver ovallSaver(strSave, ios_base::out|ios_base::app);
	Timer tm;

	double temperature = maxT;
    double absoluteTemperature = 0.00001;
    int iteration = 0;
    int pos1, pos2;

    int shortest = distance;
    int deltaDistance;

    tm.start();

    //would went into deadlock otherwise
    if (pgenData->getNumberOfCities() < 2) {
    	return NULL;
    }

    //cout << fixed << "temperature: " <<temperature << " abs: " << absoluteTemperature << endl;
    //cout << "cRate: " << cRate << endl;

    while (temperature > absoluteTemperature)
    {
    	//neighbourhood has been searched completely, and
    	//no better result has been found

    	//find next using 2-opt transformation
    	pos1 = rand()% pgenData->getNumberOfCities();

    	do {
    		pos2 = rand() % pgenData->getNumberOfCities();
    	} while (pos1 == pos2);

        nextOrder = new vector<int>(*res);
        ChangeMaker::transform_2opt(nextOrder, pos1, pos2);

        deltaDistance = pgenData->calculateWholeDistance(nextOrder) - distance;

        //if the new order has a smaller distance
        //or if the new order has a larger distance but
        //satisfies Boltzman condition then accept the arrangement
        if ((deltaDistance < 0) ||
        		(distance > 0 && exp(((double)(-deltaDistance) / temperature)) > SA::nextDouble()))
        {
        	//cout <<"new result" << endl;
            delete res;
            res = nextOrder;
            distance = deltaDistance + distance;
            if (deltaDistance < 0) {
            	//cout << "new shortest: " <<distance << endl;
            	delete best;
            	best = new vector<int>(*nextOrder);
				shortest = distance;
            }
        } else {
        	delete nextOrder;
        }

        //cool down the temperature
        temperature *= cRate;

        //tmSaver.saveLine(tm.getRunTime(), distance);
        //itSaver.saveLine(iteration, distance);

        iteration++;
    }
    cout << "iterations: " << iteration << " : " << shortest << endl;
    ovallSaver.saveOverallLine(ovFileName, tm.getRunTime(), iteration +1, iteration+1, distance);


    delete res;
	return best;
}


double SA::nextDouble() {
	int x = rand();
	return (double)x/(double)RAND_MAX;
}
