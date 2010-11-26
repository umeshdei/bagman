/*
 * Result.h
 *
 *  Created on: 2010-10-26
 *      Author: prog
 */

#ifndef RESULT_H_
#define RESULT_H_

#include <vector>
#include <map>
#include <algorithm>

#include "io/Point.h"

using namespace std;

class Result : public std::vector<Point *>
{
public:
	Result();
	void setCalculatedDistance(u_int32_t dist) { _calculatedDistance = dist; }
	u_int32_t getCalculatedDistance() { return _calculatedDistance; }
	void print(bool only_distance = false);
	void setNeighborsVisited(u_int32_t n) { _neighorsVisited = n; }
	u_int32_t getNeighborsVisited() { return _neighorsVisited; }
	void setBetterSolutionsCount(u_int32_t n) { _betterSolutions = n; }
	u_int32_t getBetterSolutionsCount() { return _betterSolutions; }
	void setStepsCount(u_int32_t n) { _stepsCount = n; }
	u_int32_t getStepsCount() { return _stepsCount; }
	void swapRandomly();
	map<double, u_int32_t> *getScores() { return &_scores; }
	virtual ~Result();

private:
	u_int32_t _neighorsVisited;
	u_int32_t _betterSolutions;
	u_int32_t _stepsCount;
	map<double, u_int32_t> _scores;
	u_int32_t _calculatedDistance;
};

#endif /* RESULT_H_ */
