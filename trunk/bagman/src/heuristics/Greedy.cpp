/*
 * Greedy.cpp
 *
 *  Created on: Nov 6, 2010
 *      Author: piekar294
 */

#include "Greedy.h"

Greedy::Greedy(string strSave) : Calculation(strSave) {
}

Greedy::~Greedy() {
	// TODO Auto-generated destructor stub
}

vector<int> *Greedy::solve(Generate *pgenData, string ovFileName) {
	return solve(pgenData, UINT_MAX, ovFileName);
}

vector<int> *Greedy::solve(Generate *pgenData, unsigned int pintMaxIterCount, string ovFileName) {
	_timer.start();

	DataSaver *vSaver = DataSaver::GetIterationFile(ovFileName + ".vec");

	int noSeenN = 0;
	vector<int> *best = pgenData->getRandomResult();

	int bestScore = pgenData->calculateWholeDistance(best);

	Transformation *t = new Transformation2OPT();
	vector<int> *current = NULL;
	bool progress; //contains progress flag

	_ovallSaver->saveOverallLine(ovFileName, _timer.getRunTime(), 0, 0, bestScore);

	for (unsigned int i = 0; i < pintMaxIterCount; i++) {
		progress = false;
		t->reset(best);
		//iterate until better solution is found
		while(t->getNext(&current)) {
			noSeenN++;
			int currScore = pgenData->calculateWholeDistance(current);
			if (currScore < bestScore) {
				progress = true;
				delete best;
				best = current;
				bestScore = currScore;
				break;
			} else {
				delete current;
			}
		}
		_ovallSaver->saveOverallLine(ovFileName, _timer.getRunTime(), i+1, noSeenN, bestScore);


		if (!progress) {

			vSaver->saveLine("greedy", best);
			delete vSaver;
			return best;
		}
	}

	vSaver->saveLine("greedy", best);
	delete vSaver;
	return best;
}
