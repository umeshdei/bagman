/*
 * Tabu.cpp
 *
 *  Created on: Nov 30, 2010
 *      Author: piekar294
 */

#include "Tabu.h"

//neighSearched is a unsigned int from <1; 100>. It is a % value, indicates % of neighbourhood searched.
Tabu::Tabu(unsigned int tabuSize, unsigned int neighSearched, unsigned int iterationsNo, string strSave):
Calculation(strSave), _tabuSize(tabuSize), _neighSerchPercent(neighSearched), _iterationsNo(iterationsNo) {
	distanceMax = -10000000;
}

Tabu::~Tabu() {
	// TODO Auto-generated destructor stub
}


vector<int> *Tabu::solve(Generate *pgenData, string ovFileName) {
	_timer.start();

	TSList tabuList(_tabuSize);
	DataSaver *vSaver = DataSaver::GetIterationFile(ovFileName + ".vec");

	int noSeenN = 0;
	vector<int> *best = pgenData->getRandomResult();

	int bestScore = pgenData->calculateWholeDistance(best);
	vector<int> *actualBest =  new vector<int>(*best);
	int actualBestDist;
	int actualBestScore;
	TSSwap actualBestSwap;
	TSSwap move;

	Transformation *t = new Transformation2OPT();
	vector<int> *current = NULL;

	_ovallSaver->saveOverallLine(ovFileName, _timer.getRunTime(), 0, 0, bestScore);

	for (unsigned int i = 0; i < _iterationsNo; i++) {
		t->reset(actualBest);
		actualBestDist = distanceMax;
		//iterate through neighbourhood
		while(t->hasNext()) {
			bool check = ((unsigned int)(rand() % 100) < _neighSerchPercent) ? true : false;
			if (check) {
				noSeenN++;
				(dynamic_cast<Transformation2OPT*>(t))->getNextSwap(move);
				t->next(&current);
				int currScore = pgenData->calculateWholeDistance(current);
				int currDist = this->distanceFromBest(bestScore, currScore);

				//check tabu list
				if (!tabuList.checkMove(&move)) {
					//check aspiration criteria and continue
					if ((currScore > bestScore) && (currDist > actualBestDist) ) {
						delete actualBest;
						delete best;

						bestScore = currScore;
						//need to be copied, problem with multiple delete
						best = new vector<int>(*current);

						actualBest = current;
						actualBestDist = currDist;
						actualBestSwap = move;
						actualBestScore = currScore;
					} else {
						delete current;
					}
					continue;
				}

				//ususal case, neighbour not in the tabu list
				if (currDist > actualBestDist) {
					delete actualBest;

					actualBest = current;
					actualBestDist = currDist;
					actualBestSwap = move;
					actualBestScore = currScore;
				} else {
					delete current;
				}
			} else { //neighbour skipped
				t->moveNext();
			}

		}

		if (actualBestScore > bestScore) {
			delete best;
			bestScore = actualBestScore;
		}
		_ovallSaver->saveOverallLine(ovFileName, _timer.getRunTime(), i+1, noSeenN, bestScore);
	}

	vSaver->saveLine("tabu", best);
	delete vSaver;
	return best;
}

vector<int> *Tabu::solve(Generate *pgenData, unsigned int pintMaxIterCount, string ovFileName) {
	this->_iterationsNo = pintMaxIterCount;
	return this->solve(pgenData, ovFileName);
}

