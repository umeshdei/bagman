/*
 * TSPRandomSolver.cpp
 *
 *  Created on: 2010-10-26
 *      Author: prog
 */

#include "TSPRandomSolver.h"

TSPRandomSolver::TSPRandomSolver(Instance *inst, string output) : TSPSolver(output)
{
	TSPSolver::_instance = inst;
	saver = new TSPDataSaver(output.c_str(), inst);
}

TSPRandomSolver::TSPRandomSolver(u_int32_t size, string output) : TSPSolver(output)
{
	_instance = Instance::generateRandomInstance(size);
	saver = new TSPDataSaver(output.c_str(), _instance);
}

void TSPRandomSolver::setStepsCount(u_int32_t stepsCount)
{
	_stepsCount = stepsCount;
}

Result *TSPRandomSolver::solve()
{
	Timer timer;
	u_int32_t bestDistance, currDistance;
	u_int32_t betterSolutionsCount = 0;
	Result *curr, *bestResult;
	Result best;

	curr = generateRandomResult();
	bestDistance = calculateDistance(curr);
	curr->setCalculatedDistance(bestDistance);
	//curr->print(true);
	best = *curr;

	timer.start();
	for (u_int32_t i = 0; i < _stepsCount; i++)
	{
		randomizeResult(curr);
		currDistance = calculateDistance(curr);
		curr->setCalculatedDistance(currDistance);
		if (currDistance < bestDistance)
		{
			betterSolutionsCount++;
			//curr->print(true);
			bestDistance = currDistance;
			best = *curr;
		}
		u_int32_t a = i%(u_int32_t)FREQUENCY_SAVER;
		//cout << a << endl;
		if(a == 0)
		{
			std::stringstream out;
			out << i;
			out << " ";
			out << best.getCalculatedDistance();
			out << " " << timer.getRunTime();
			saver->saveLine(out.str());
		}
	}

	bestResult = new Result(best);
	//bestResult->print();
	delete curr;

	bestResult->setStepsCount(_stepsCount);
	bestResult->setBetterSolutionsCount(betterSolutionsCount);

	return bestResult;
}

TSPRandomSolver::~TSPRandomSolver()
{
	delete saver;
}
