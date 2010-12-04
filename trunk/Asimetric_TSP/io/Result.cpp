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
		int i = 0;
		for (; it != end(); it++)
		{
			printf("-> %d ", (*it)->getNum());
		}
	}
	printf(" (distance: %d)\n", _calculatedDistance);
}

void Result::swapRandomly() {
	int i;
	int j;
	i = (int)rand() % this->size();
	j = (int)rand() % this->size();
	//cout << this->size() << endl;
	//cout << (*this)[i] << endl;
	//cout << (rand() * this->size()) << " " << (rand() * this->size()) % this->size() << endl;
	//cout << "zamieniam: " << i << " z " << j << endl;
	std::swap((*this)[i], (*this)[j]);
}

Result::~Result()
{

}
