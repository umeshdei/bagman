/*
 * TSPSteepestSolver.cpp
 *
 *  Created on: 2010-10-28
 *      Author: kolczak
 */

#include "TSPSteepestSolver.h"


TSPSteepestSolver::TSPSteepestSolver(Instance *inst, string output) : TSPSolver(output)
{
	TSPSolver::_instance = inst;
	saver = new TSPDataSaver(output.c_str(), inst);
}

TSPSteepestSolver::TSPSteepestSolver(u_int32_t size, string output) : TSPSolver(output)
{
	_instance = Instance::generateRandomInstance(size);
	saver = new TSPDataSaver(output.c_str(), _instance);
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
	u_int32_t neighorsVisited = 0, betterSolutionsCount = 0;
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
				betterSolutionsCount++;
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

	bestResult->setNeighborsVisited(neighorsVisited);
	bestResult->setStepsCount(numberOfSteps);
	bestResult->setBetterSolutionsCount(betterSolutionsCount);
	//bestResult->print();
	delete pure;

	return bestResult;
}

Result *TSPSteepestSolver::solve()
{
	u_int32_t frequency;
	Timer timer;
	u_int32_t bestDistance;
	Result *curr;
	Result *best;

	frequency = _stepsCount / 100;
	if (frequency < FREQUENCY_SAVER)
		frequency = FREQUENCY_SAVER;

	curr = generateRandomResult();
	bestDistance = calculateDistance(curr);
	curr->setCalculatedDistance(bestDistance);

	timer.start();
	for (u_int32_t i = 0; i < _stepsCount; i++)
	{
		best = checkNeighbours(curr);
		//co zrobic jak nie znalazlo wsrod sasiadow polepszenia rozwiazania?
		if (curr->getCalculatedDistance() <= best->getCalculatedDistance())
		{
			return best;
		}
		curr = best;
		u_int32_t a = i % (u_int32_t)frequency;
		if (a == 0)
		{
			std::stringstream out;
			out << i;
			out << " ";
			out << best->getCalculatedDistance();
			out << " " << timer.getRunTime();
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
