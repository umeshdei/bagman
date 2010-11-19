/*
 * SA.cpp
 *
 *  Created on: Nov 19, 2010
 *      Author: piekar294
 */

#include "SA.h"

SA::SA() {
	// TODO Auto-generated constructor stub

}

SA::~SA() {
	// TODO Auto-generated destructor stub
}

vector<int> *SA::solve(Generate *pgenData, string ovFileName, double maxT, double cRate) {
	vector<int> *res = pgenData->getRandomResult();
	vector<int> *nextOrder;
	int distance = pgenData->calculateWholeDistance(res);


	double temperature = maxT;
    double absoluteTemperature = 0.00001;
    int iteration = 0;
    Transformation2OPT tr(res);

    int shortest = distance;
    int deltaDistance;

    while (temperature > absoluteTemperature)
    {
    	//neighbourhood has been searched completely, and
    	//no better result has been found
    	if (tr.getNext(&nextOrder) == false) {
    		break;
    	}

        deltaDistance = pgenData->calculateWholeDistance(nextOrder) - distance;

        //if the new order has a smaller distance
        //or if the new order has a larger distance but
        //satisfies Boltzman condition then accept the arrangement
        if ((deltaDistance < 0) ||
        		(distance > 0 && exp(((double)(-deltaDistance) / temperature)) > SA::nextDouble()))
        {
            delete res;
            res = nextOrder;
            tr.reset(res);
            distance = deltaDistance + distance;
            if (deltaDistance < 0) {
				shortest = distance;
            }
        }

        //cool down the temperature
        temperature *= cRate;

        iteration++;
    }

    shortest = distance;
	return res;
}


double SA::nextDouble() {
	int x = rand();
	return (double)x/(double)RAND_MAX;
}
