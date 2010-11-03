/*
 * TSPRandomSolver.cpp
 *
 *  Created on: 2010-10-26
 *      Author: prog
 */

#include "TSPRandomSolver.h"

TSPRandomSolver::TSPRandomSolver(Instance *inst)
{
	TSPSolver::_instance = inst;
}

TSPRandomSolver::TSPRandomSolver(u_int32_t size)
{
	_instance = Instance::generateRandomInstance(size);
}

void TSPRandomSolver::setStepsCount(u_int32_t stepsCount)
{
	_stepsCount = stepsCount;
}

Result *TSPRandomSolver::solve()
{
	u_int32_t bestDistance, currDistance;
	Result *curr, *bestResult;
	Result best;

	curr = generateRandomResult();
	bestDistance = calculateDistance(curr);
	curr->setCalculatedDistance(bestDistance);
	curr->print(true);
	best = *curr;

	for (u_int32_t i = 0; i < _stepsCount; i++)
	{
		randomizeResult(curr);
		currDistance = calculateDistance(curr);
		curr->setCalculatedDistance(currDistance);
		if (currDistance < bestDistance)
		{
			curr->print(true);
			bestDistance = currDistance;
			best = *curr;
		}
	}

	bestResult = new Result(best);
	bestResult->print();
	delete curr;

	return bestResult;
}

TSPRandomSolver::~TSPRandomSolver()
{

}
