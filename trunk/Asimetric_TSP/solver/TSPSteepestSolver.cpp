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
	saver = new TSPDataSaver("steepest", inst);
}

TSPSteepestSolver::TSPSteepestSolver(u_int32_t size)
{
	_instance = Instance::generateRandomInstance(size);
	saver = new TSPDataSaver("steepest", _instance);
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
			std::swap(changed[i], changed[j]);

			neighorsVisited++;
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
		numberOfSteps++;
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

	//cout << "Rozwiazuje steepest" << endl;

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
		u_int32_t a = i%(u_int32_t)FREQUENCY_SAVER;
		//cout << a << endl;
		if(a == 0)
		{
			std::stringstream out;
			out << i;
			out << " ";
			out << best->getCalculatedDistance();
			saver->saveLine(out.str());
		}
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
	delete saver;
}
