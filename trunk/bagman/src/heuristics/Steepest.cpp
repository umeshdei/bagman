/*
 * Steepest.cpp
 *
 *  Created on: Nov 9, 2010
 *      Author: piekar294
 */

#include "Steepest.h"

Steepest::Steepest(string strSave) : Calculation(strSave){
}

Steepest::~Steepest() {
	// TODO Auto-generated destructor stub
}

vector<int> *Steepest::solve(Generate *pgenData, string ovFileName) {
	return solve(pgenData, UINT_MAX, ovFileName);
}

vector<int> *Steepest::solve(Generate *pgenData, unsigned int pintMaxIterCount, string ovFileName) {

	DataSaver *vSaver = DataSaver::GetIterationFile(ovFileName + ".vec");

	_timer.start();
	int noSeenN = 0;
	vector<int> *best = pgenData->getRandomResult();
	int bestScore = pgenData->calculateWholeDistance(best);
	Transformation *t = new Transformation2OPT();
	vector<int> *current = NULL;
	bool progress; //contains progress flag
	//iterate through all neightbours

	//save initial values
	_ovallSaver->saveOverallLine(ovFileName, _timer.getRunTime(), 0, 0, bestScore);

	for (unsigned int i = 0; i < pintMaxIterCount; i++) {
		progress = false;
		t->reset(best);
		//iterate through all neightbours (do not break if better solution is found)
		while(t->getNext(&current)) {
			noSeenN++;
			int currScore = pgenData->calculateWholeDistance(current);
			if (currScore < bestScore) {
				progress = true;
				delete best;
				best = current;
				bestScore = currScore;
			} else {
				delete current;
			}
		}
		//save current score
		_ovallSaver->saveOverallLine(ovFileName, _timer.getRunTime(), i+1, noSeenN, bestScore);

		if (!progress) {
			vSaver->saveLine("steepest", best);
			delete vSaver;
			return best;
		}
	}

	//return best after max iteration amount
	vSaver->saveLine("steepest", best);
	delete vSaver;
	return best;
}
