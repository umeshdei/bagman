/*
 * TSPTabuSearchSolver.cpp
 *
 *  Created on: 2010-11-26
 *      Author: kolczak
 */

#include "TSPTabuSearchSolver.h"

TSPTabuSearchSolver::TSPTabuSearchSolver(Instance *inst, string output) : TSPSolver(output) {
	// TODO Auto-generated constructor stub
	TSPSolver::_instance = inst;
	saver = new TSPDataSaver(output.c_str(), inst);
	_tabuList = new TabuList();
}

TSPTabuSearchSolver::TSPTabuSearchSolver(u_int32_t size, string output) : TSPSolver(output) {
	_instance = Instance::generateRandomInstance(size);
	saver = new TSPDataSaver(output.c_str(), _instance);
	_tabuList = new TabuList();
}

u_int32_t neighorsVisited = 0, betterSolutionsCount = 0;
/**
 * funkcja wybierajaca najlepszego z sasiadujacych rozwiazan
 */
Result *TSPTabuSearchSolver::bestPossibleNeighbour(Result* pure, Result *bestKnown)
{
	Point *p = new Point();
	u_int32_t bestDistance, changedDistance;
	Result *best, *changed;

	best = new Result(*pure);
	changed = pure;

	bestDistance = pure->getCalculatedDistance();


	for (u_int32_t i = 0; i < pure->size() - 1; i++)
	{
		for (u_int32_t j = i+1; j < pure->size(); j++)
		{
			//zamiana elementów
			//cout << "rozmiar tablicy: " << changed->size() << endl;
			//cout << "zamieniam: " << i << " z " << j << " czyli wartosć: " << (*changed)[i] << " z " << (*changed)[j] << endl;
			//cout << "przed zamiana: " ;
			//changed->print();
			std::swap((*changed)[i], (*changed)[j]);
			//cout << "po zamianie: " ;
			//changed->print();

			neighorsVisited++;
			changedDistance = calculateDistance(changed);
			p->setX(i);
			p->setY(j);
			//sprawdzamy czy rozwiązanie spełnia warunku przyjęcia
			//jezeli poprawia globalne najlepsze rozwiazanie
			if (changedDistance < bestKnown->getCalculatedDistance()) {
				delete bestKnown;
				bestKnown = new Result(*changed);
				bestKnown->setCalculatedDistance(changedDistance);

				delete best;
				best = new Result(*changed);
				best->setCalculatedDistance(changedDistance);

				if(!_tabuList->isInTabu(p))
					_tabuList->addToList(p);

				betterSolutionsCount++;
			}
			//albo jest to jak na razie najlepszy z sasiadow nie znajdujacy sie na liscie tabu
			else if	( (changedDistance < best->getCalculatedDistance()) && (!(_tabuList->isInTabu(p))) ) {
				delete best;
				best = new Result(*changed);
				best->setCalculatedDistance(changedDistance);

				_tabuList->addToList(p);

				betterSolutionsCount++;
			}
			//odmiana elementów
			std::swap((*changed)[i], (*changed)[j]);
		}
	}
	delete p;

	return best;
}

Result *TSPTabuSearchSolver::solve() {
	/**
		k := 1.
		generate initial solution
		WHILE the stopping condition is not met DO
			Identify N(s). (Neighbourhood set)
			Identify T(s,k). (Tabu set)
			Identify A(s,k). (Aspirant set)
			Choose the best s’ Î  N(s,k) = {N(s) - T(s,k)}+A(s,k).
			Memorize s’ if it improves the previous best known solution
			s := s’.
			k := k+1.
		END WHILE
	 */
	Result *cur;
	Result *next;
	Result *bestKnown = NULL;
	u_int32_t loopCounter = 0;

	//początkowe rozwiązanie
	cur = generateRandomResult();
	bestKnown = new Result(*cur);

	while ( loopCounter < getNumberOfSteps() ) {

		next = bestPossibleNeighbour(cur, bestKnown);
		delete cur;
		cur = next;

		loopCounter++;
	}

	bestKnown->setNeighborsVisited(neighorsVisited);
	bestKnown->setStepsCount(loopCounter);
	bestKnown->setBetterSolutionsCount(betterSolutionsCount);

	return bestKnown;
}

TSPTabuSearchSolver::~TSPTabuSearchSolver() {
	delete saver;
	delete _tabuList;
	// TODO Auto-generated destructor stub
}
