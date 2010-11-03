/*
 * Result.h
 *
 *  Created on: 2010-10-26
 *      Author: prog
 */

#ifndef RESULT_H_
#define RESULT_H_

#include <vector>

#include "io/Point.h"

class Result : public std::vector<Point *>
{
public:
	Result();
	void setCalculatedDistance(u_int32_t dist) { _calculatedDistance = dist; }
	u_int32_t getCalculatedDistance() { return _calculatedDistance; }
	void print(bool only_distance = false);
	virtual ~Result();

private:
	u_int32_t _calculatedDistance;
};

#endif /* RESULT_H_ */
