/*
 * Instance.h
 *
 *  Created on: 2010-10-26
 *      Author: prog
 */

#ifndef INSTANCE_H_
#define INSTANCE_H_

#include <stdlib.h>
#include <stdio.h>
#include "Point.h"

class Instance
{
public:
	Instance(u_int32_t size);
	virtual ~Instance();
	u_int32_t getPointsDistance(u_int32_t i, u_int32_t j);
	Point *getPoint(u_int32_t i);
	u_int32_t getSize();

	void print();
	static Instance *generateRandomInstance(u_int32_t size, int seed = 0);

private:
	u_int32_t _size;
	u_int32_t **_distanceMatrix;
	Point **_pointArray;
};

#endif /* INSTANCE_H_ */
