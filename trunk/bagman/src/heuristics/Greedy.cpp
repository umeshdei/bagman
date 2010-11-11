/*
 * Greedy.cpp
 *
 *  Created on: Nov 6, 2010
 *      Author: piekar294
 */

#include "Greedy.h"

Greedy::Greedy() {
	// TODO Auto-generated constructor stub

}

Greedy::~Greedy() {
	// TODO Auto-generated destructor stub
}

vector<int> *Greedy::solve(Generate *pgenData) {
	return solve(pgenData, INT_MAX);
}

vector<int> *Greedy::solve(Generate *pgenData, int pintMaxIterCount) {
	vector<int> *best = pgenData->getRandomResult();
	int bestScore = pgenData->calculateWholeDistance(best);
	Transformation *t = new Transformation2OPT();
	vector<int> *current = NULL;
	bool progress; //contains progress flag

	for (int i = 0; i < pintMaxIterCount; i++) {
		progress = false;
		t->reset(best);
		//iterate until better solution is found
		while(t->getNext(&current)) {
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
		if (!progress) {
			return best;
		}
	}

	//return best after max iteration amount
	return best;
}
