/*
 * Result.cpp
 *
 *  Created on: 2010-10-26
 *      Author: prog
 */

#include "Result.h"

Result::Result()
{
}

void Result::print(bool only_distance)
{
	Result::iterator it;

	if (!only_distance)
	{
		it = begin();
		printf("%d ", (*it)->getNum());
		it++;
		for (; it != end(); it++)
		{
			printf("-> %d ", (*it)->getNum());
		}
	}
	printf(" (distance: %d)\n", _calculatedDistance);
}

Result::~Result()
{

}
