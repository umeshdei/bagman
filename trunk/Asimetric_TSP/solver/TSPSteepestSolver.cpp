/*
 * TSPSteepestSolver.cpp
 *
 *  Created on: 2010-10-28
 *      Author: kolczak
 */

#include "TSPSteepestSolver.h"

TSPSteepestSolver::TSPSteepestSolver(Instance *inst)
{
	TSPSolver::_instance = inst;
}

TSPSteepestSolver::TSPSteepestSolver(u_int32_t size)
{
	_instance = Instance::generateRandomInstance(size);
}

void TSPSteepestSolver::setStepsCount(u_int32_t stepsCount)
{
	_stepsCount = stepsCount;
}

/**
 * funkcja wybierajaca najlepszego z sasiadujacych rozwiazan
 */
Result *TSPSteepestSolver::checkNeighbours(Result* pure)
{
	u_int32_t bestDistance, changedDistance;
	Result *bestResult;
	Result best, changed;
	best = *pure;
	changed = *pure;
	bestDistance = pure->getCalculatedDistance();
	best.setCalculatedDistance(bestDistance);

	for (u_int32_t i = 0; i < pure->size() - 1; i++)
	{
		for (u_int32_t j = 1; j < pure->size(); j++)
		{
			/*
			tmp1 = changed[i];
			changed[i] = changed[j];
			changed[j] = tmp1;
			*/
			std::swap(changed[i], changed[j]);
			changedDistance = calculateDistance(&changed);
			//jezeli natrafilismy na lepsze rozwiazanie
			if (changedDistance < bestDistance)
			{
				bestDistance = changedDistance;
				best = changed;
				best.setCalculatedDistance(bestDistance);
				//best.print(true);
			}
			//changed = *pure;
			std::swap(changed[i], changed[j]);
		}
	}
	bestResult = new Result(best);
	//bestResult->print();
	delete pure;

	return bestResult;
}

Result *TSPSteepestSolver::solve()
{
	u_int32_t bestDistance;
	Result *curr;
	Result *best;

	curr = generateRandomResult();
	bestDistance = calculateDistance(curr);
	curr->setCalculatedDistance(bestDistance);
	//curr->print();

	for (u_int32_t i = 0; i < _stepsCount; i++)
	{
		best = checkNeighbours(curr);
		//co zrobic jak nie znalazlo wsrod sasiadow polepszenia rozwiazania?
		if (curr->getCalculatedDistance() <= best->getCalculatedDistance())
		{
			return best;
			/*
			 bestResult = new Result(best);
			 bestResult->print();
			 delete best;

			 return bestResult;
			 */
		}
		curr = best;
		//printf("lepsze rozwiazanie: %d\n", best->getCalculatedDistance());
	}

	/*
	 bestResult = new Result(best);
	 bestResult->print();
	 delete best;
	 */
	return best;
}

TSPSteepestSolver::~TSPSteepestSolver()
{

}
