#include "TSPTabuSearchSolver.h"

TSPTabuSearchSolver::TSPTabuSearchSolver(Instance *inst, string output, u_int32_t tabuListSize) : TSPSolver(output)
{
	// TODO Auto-generated constructor stub
	TSPSolver::_instance = inst;
	saver = new TSPDataSaver(output.c_str(), inst);
	_tabuList = new TabuList(tabuListSize);
	neighorsVisited = 0;
	betterSolutionsCount = 0;
	_badMoves = 0;
}

TSPTabuSearchSolver::TSPTabuSearchSolver(u_int32_t size, string output, u_int32_t tabuListSize) : TSPSolver(output)
{
	_instance = Instance::generateRandomInstance(size);
	saver = new TSPDataSaver(output.c_str(), _instance);
	_tabuList = new TabuList(tabuListSize);
	neighorsVisited = 0;
	betterSolutionsCount = 0;
}

/**
 * funkcja wybierajaca najlepszego z sasiadujacych rozwiazan
 */
Result *TSPTabuSearchSolver::bestPossibleNeighbour(Result* pure, Result **bestKnown)
{
	Point p;
	u_int32_t bestDistance = 0, changedDistance = 0;
	Result *best, *changed;

	best = new Result(*pure);
	changed = pure;

	//bestDistance = pure->getCalculatedDistance();
	bestDistance = 1000000000;

	for (u_int32_t i = 0; i < pure->size() - 1; i++)
	{
		for (u_int32_t j = i + 1; j < pure->size(); j++)
		{
			std::swap((*changed)[i], (*changed)[j]);

			neighorsVisited++;
			changedDistance = calculateDistance(changed);
			p.setX(i);
			p.setY(j);

			//sprawdzamy czy rozwiązanie spełnia warunku przyjęcia
			//jezeli poprawia globalne najlepsze rozwiazanie
			if (changedDistance < (*bestKnown)->getCalculatedDistance())
			{
				delete *bestKnown;
				(*bestKnown) = new Result(*changed);
				(*bestKnown)->setCalculatedDistance(changedDistance);

				delete best;
				best = new Result(*changed);
				best->setCalculatedDistance(changedDistance);
				betterSolutionsCount++;
			}

			if (!_tabuList->isInTabu(&p))
			{
				//albo jest to jak na razie najlepszy z sasiadow nie znajdujacy sie na liscie tabu
				if (changedDistance < bestDistance)
				{
					bestDistance = changedDistance;
					delete best;
					best = new Result(*changed);
					best->setCalculatedDistance(changedDistance);
					_tabuList->addToList(&p);
				}
			}

			std::swap((*changed)[i], (*changed)[j]);
		}
	}

	return best;
}

Result *TSPTabuSearchSolver::solve()
{
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
	u_int32_t loopCounter = 0, bestDistance = 0;

	//początkowe rozwiązanie
	cur = generateRandomResult();
	bestKnown = generateRandomResult();
	bestDistance = bestKnown->getCalculatedDistance();

	while (loopCounter < getNumberOfSteps() && _maxBadMoves > _badMoves)
	{
		next = bestPossibleNeighbour(cur, &bestKnown);
		if (bestDistance <= next->getCalculatedDistance())
		{
			++_badMoves;
			if (_badMoves % 50 == 0)
			{
				delete next;
				next = generateRandomResult();
			}
		}
		else
		{
			bestDistance = next->getCalculatedDistance();
		}
		delete cur;
		cur = next;

		loopCounter++;
	}

	bestKnown->setNeighborsVisited(neighorsVisited);
	bestKnown->setStepsCount(loopCounter);
	bestKnown->setBetterSolutionsCount(betterSolutionsCount);

	return bestKnown;
}

TSPTabuSearchSolver::~TSPTabuSearchSolver()
{
	delete saver;
	delete _tabuList;
	// TODO Auto-generated destructor stub
}
