/*
 * Greedy.cpp
 *
 *  Created on: Nov 6, 2010
 *      Author: piekar294
 */

#include "Greedy.h"

Greedy::Greedy(string strTimeFileName, string strIterationFileName, string strStepFileName) : Calculation(strTimeFileName, strIterationFileName, strStepFileName) {
	// TODO Auto-generated constructor stub
}

Greedy::Greedy(string strFileName) : Calculation(strFileName) {
	// TODO Auto-generated constructor stub
}

Greedy::Greedy() {
}

Greedy::~Greedy() {
	// TODO Auto-generated destructor stub
}

vector<int> *Greedy::solve(Generate *pgenData, string fileName) {
	return solve(pgenData, INT_MAX, fileName);
}

vector<int> *Greedy::solve(Generate *pgenData, int pintMaxIterCount, string fileName) {
	string iFileName = fileName + ".iter";
	string tFileName = fileName + ".tm";
	string vFileName = fileName + ".vec";
	DataSaver *vSaver = DataSaver::GetIterationFile(vFileName);
	DataSaver *iSaver = DataSaver::GetIterationFile(iFileName);
	DataSaver *tSaver = DataSaver::GetTimeFile(tFileName);

	_timer.start();

	vector<int> *best = pgenData->getRandomResult();
	int bestScore = pgenData->calculateWholeDistance(best);
	Transformation *t = new Transformation2OPT();
	vector<int> *current = NULL;
	bool progress; //contains progress flag

	//save initial values
	iSaver->saveLine(0, bestScore);
	tSaver->saveLine(_timer.getRunTime(), bestScore);

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
		//save current score
		iSaver->saveLine(i+1, bestScore);
		tSaver->saveLine(_timer.getRunTime(), bestScore);

		if (!progress) {
			vSaver->saveLine(best);
			delete vSaver;
			delete iSaver;
			delete tSaver;
			return best;
		}
	}

	//return best after max iteration amount
	vSaver->saveLine(best);
	delete vSaver;
	delete iSaver;
	delete tSaver;
	return best;
}
