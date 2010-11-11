/*
 * Steepest.cpp
 *
 *  Created on: Nov 9, 2010
 *      Author: piekar294
 */

#include "Steepest.h"

Steepest::Steepest(string strOutputFileName) : Calculation(strOutputFileName) {
	// TODO Auto-generated constructor stub

}

Steepest::~Steepest() {
	// TODO Auto-generated destructor stub
}

vector<int> *Steepest::solve(Generate *pgenData) {
	return solve(pgenData, INT_MAX);
}

vector<int> *Steepest::solve(Generate *pgenData, int pintMaxIterCount) {
	_timer.start();
	vector<int> *best = pgenData->getRandomResult();
	int bestScore = pgenData->calculateWholeDistance(best);
	Transformation *t = new Transformation2OPT();
	vector<int> *current = NULL;
	bool progress; //contains progress flag
	//iterate through all neightbours


	for (int i = 0; i < pintMaxIterCount; i++) {
		progress = false;
		t->reset(best);
		//iterate through all neightbours (do not break if better solution is found)
		while(t->getNext(&current)) {
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
		if (!progress) {
			return best;
		}
	}

	//return best after max iteration amount
	return best;
}
