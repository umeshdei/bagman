/*
 * Instance.cpp
 *
 *  Created on: 2010-10-26
 *      Author: prog
 */

#include "Instance.h"
#include "tsp.h"

Instance::Instance(u_int32_t size)
{
	_size = size;
	_distanceMatrix = new u_int32_t* [size];
	_pointArray = new Point* [size];
	for (u_int32_t i = 0; i < size; i++)
	{
		_distanceMatrix[i] = new u_int32_t[size];
		_distanceMatrix[i][i] = 1;
	}
}

Instance *Instance::generateRandomInstance(u_int32_t size, int seed)
{
	Instance *instance = new Instance(size);
	for (u_int32_t i = 0; i < size; i++)
	{
		instance->_pointArray[i] = Point::generatePoint(i);
		//instance->_pointArray[i]->setNum(i);
	}

	for (u_int32_t i = 0; i < size; i++)
	{
		for (u_int32_t j = 0; j < i; j++)
		{
			instance->_distanceMatrix[i][j] = instance->_pointArray[i]->calcDistance(*(instance->_pointArray[j]));
			instance->_distanceMatrix[j][i] =
				instance->_distanceMatrix[i][j] * (1 - 0.5 * ((float)(rand() % TSP_RAND_MAX - rand() % TSP_RAND_MAX) / TSP_RAND_MAX));
		}
	}

	return instance;
}

u_int32_t Instance::getPointsDistance(u_int32_t i, u_int32_t j)
{
	return _distanceMatrix[i][j];
}

Point *Instance::getPoint(u_int32_t i)
{
	return _pointArray[i];
}

u_int32_t Instance::getSize()
{
	return _size;
}

void Instance::print()
{
	printf("=========== point array =============\n");
	for (u_int32_t i = 0; i < _size; i++)
	{
		printf("%u. ", i);
		_pointArray[i]->print();
	}

	printf("=========== distance matrix =============\n");
	for (u_int32_t i = 0; i < _size; i++)
	{
		for (u_int32_t j = 0; j < _size; j++)
		{
			printf("%5u ", _distanceMatrix[i][j]);
		}
		printf("\n");
	}
}

Instance::~Instance()
{
	for (u_int32_t i = 0; i < _size; i++)
		delete _distanceMatrix[i];
	delete _distanceMatrix;
	delete _pointArray;
}
