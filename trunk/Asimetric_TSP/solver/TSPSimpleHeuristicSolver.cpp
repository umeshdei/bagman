/*
 * TSPSimpleHeuristicSolver.cpp
 *
 *  Created on: 2010-11-07
 *      Author: prog
 */

#include "TSPSimpleHeuristicSolver.h"

TSPSimpleHeuristicSolver::TSPSimpleHeuristicSolver()
{

}

Result *TSPSimpleHeuristicSolver::solve()
{
	bool foundBetter = false;
	u_int32_t bestDistance, changedDistance;
	Result *best, changed;

	best = generateRandomResult();
	bestDistance = calculateDistance(best);
	best->setCalculatedDistance(bestDistance);
	changed = *best;
//
//	for (u_int32_t i = 0; i < _stepsCount; i++)
//	{
//		foundBetter = false;
//		for (u_int32_t j = 0; j < changed.size(); j++)
//		{
//			for (u_int32_t k = 0; k < changed.size(); k++)
//			{
//				if (j == k)
//					continue;
//
//				std::swap(changed[j], changed[k]);
//
//				changedDistance = calculateDistance(&changed);
//				if (changedDistance < bestDistance)
//				{
//					change_t ch;
//					if (lastChangesList.size() > 20)
//					{
//						lastChangesList.erase(lastChangesList.begin());
//					}
//					lastChangesList.push_back()
//					bestDistance = changedDistance;
//					*best = changed;
//					best->setCalculatedDistance(bestDistance);
//					foundBetter = true;
//					break;
//				}
//
//				std::swap(changed[j], changed[k]);
//			}
//			if (foundBetter)
//				break;
//		}
//	}
//
//	return best;
}

TSPSimpleHeuristicSolver::~TSPSimpleHeuristicSolver()
{

}
