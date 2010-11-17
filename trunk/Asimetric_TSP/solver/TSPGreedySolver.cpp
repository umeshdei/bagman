/*
 * TSPGreedySolver.cpp
 *
 *  Created on: 2010-10-28
 *      Author: prog
 */

#include "TSPGreedySolver.h"

TSPGreedySolver::TSPGreedySolver(Instance *instance, u_int32_t stepsCount)
{
	_instance = instance;
	_stepsCount = stepsCount;
}

TSPGreedySolver::TSPGreedySolver(u_int32_t instanceSize, u_int32_t stepsCount)
{
	_instance = Instance::generateRandomInstance(instanceSize, time(NULL));
	_stepsCount = stepsCount;
}

Result *TSPGreedySolver::solve()
{
	bool foundBetter = false;
	u_int32_t bestDistance, changedDistance;
	Result *best, changed;

	best = generateRandomResult();
	bestDistance = calculateDistance(best);
	best->setCalculatedDistance(bestDistance);
	//best->print();
	changed = *best;

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
				if (changedDistance < bestDistance)
				{
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
		u_int32_t a = i%(u_int32_t)FREQUENCY_SAVER;
		//cout << a << endl;
		if(a == 0)
		{
			cout << i << " " << best->getCalculatedDistance() << endl;
		}
	}

	return best;
}

TSPGreedySolver::~TSPGreedySolver()
{

}
