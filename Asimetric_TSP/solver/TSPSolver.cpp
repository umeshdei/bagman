/*
 * TSPSolver.cpp
 *
 *  Created on: 2010-10-26
 *      Author: prog
 */

#include "TSPSolver.h"

TSPSolver::TSPSolver(string output)
{
	_instance = NULL;
	numberOfSteps = 0;
	output_filename = output;
}

Result *TSPSolver::generateRandomResult()
{
	Result *res = new Result();
	if (_instance == NULL)
		return NULL;

	for (u_int32_t i = 0; i < _instance->getSize(); i++)
	{
		res->push_back(_instance->getPoint(i));
	}

	std::random_shuffle(res->begin(), res->end());

	return res;
}

void TSPSolver::randomizeResult(Result *res)
{
	std::random_shuffle(res->begin(), res->end());
}

u_int32_t TSPSolver::calculateDistance(Result *res)
{
	u_int32_t totalDistance = 0;

	for (u_int32_t i = 0; i < res->size(); i++)
	{
		totalDistance +=
			_instance->getPointsDistance(res->at(i)->getNum(), res->at((i + 1) % res->size())->getNum());
	}

	return totalDistance;
}

TSPSolver::~TSPSolver()
{

}
