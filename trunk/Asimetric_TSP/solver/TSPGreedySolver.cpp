/*
 * TSPGreedySolver.cpp
 *
 *  Created on: 2010-10-28
 *      Author: prog
 */

#include "TSPGreedySolver.h"
#include "DataSaver.h"

TSPGreedySolver::TSPGreedySolver(Instance *instance, u_int32_t stepsCount, string output) : TSPSolver(output)
{
	_instance = instance;
	_stepsCount = stepsCount;
	saver = new TSPDataSaver(output.c_str(), _instance);
}

TSPGreedySolver::TSPGreedySolver(u_int32_t instanceSize, u_int32_t stepsCount, string output) : TSPSolver(output)
{
	_instance = Instance::generateRandomInstance(instanceSize, time(NULL));
	_stepsCount = stepsCount;
	saver = new TSPDataSaver(output.c_str(), _instance);
}

Result *TSPGreedySolver::solve()
{
	Timer timer;
	bool foundBetter = false;
	u_int32_t bestDistance, changedDistance, frequency;
	u_int32_t neighorsVisited = 0, betterSolutionsCount = 0;
	Result *best, changed;

	best = generateRandomResult();
	bestDistance = calculateDistance(best);
	best->setCalculatedDistance(bestDistance);
	//best->print();
	changed = *best;

//	frequency = _stepsCount / 100;
//	if (frequency < FREQUENCY_SAVER)
	frequency = FREQUENCY_SAVER;

	timer.start();
	for (u_int32_t i = 0; i < _stepsCount; i++)
	{
		foundBetter = false;
		for (u_int32_t j = 0; j < changed.size(); j++)
		{
			for (u_int32_t k = 0; k < changed.size(); k++)
			{
				if (j == k)
					continue;

				std::swap(changed[j], changed[k]);
				neighorsVisited++;
				changedDistance = calculateDistance(&changed);
				if (changedDistance <= bestDistance)
				{
					betterSolutionsCount++;
					bestDistance = changedDistance;
					*best = changed;
					best->setCalculatedDistance(bestDistance);
					//best->print(true);
					foundBetter = true;
					break;
				}

				std::swap(changed[j], changed[k]);
			}
			numberOfSteps++;
			if (foundBetter)
				break;
		}

		//Nie ma sensu szukac dalej - w sasiedztwie nie ma lepszych rozwiazan
		if (!foundBetter)
		{
			return best;
		}
//		printf("lepsze rozwiazanie: %d\n", best->getCalculatedDistance());
		u_int32_t a = i % frequency;
		//cout << a << endl;
		if(a == 0)
		{
			std::stringstream out;
			out << i;
			out << " ";
			out << best->getCalculatedDistance();
			out << " " << timer.getRunTime();
			saver->saveLine(out.str());
		}
	}

	best->setNeighborsVisited(neighorsVisited);
	best->setStepsCount(numberOfSteps);
	best->setBetterSolutionsCount(betterSolutionsCount);

	return best;
}

TSPGreedySolver::~TSPGreedySolver()
{
	delete saver;
}
