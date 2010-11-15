/*
 * Instance.cpp
 *
 *  Created on: 2010-10-26
 *      Author: prog
 */

#include "Instance.h"
#include "tsp.h"

#include <string.h>

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
	_minLimit = 0;
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

Instance *Instance::loadFromFile(string &fileName)
{
	u_int32_t verticesCount, tmp;
	Instance *instance = NULL;

    ifstream instanceFile(fileName.c_str());
    instanceFile >> verticesCount;

    instance = new Instance((u_int32_t)verticesCount);

    for (u_int32_t i = 0; i < verticesCount; i++) {
        for (u_int32_t j = 0; j < verticesCount; j++)
        {
        	instanceFile >> tmp;
            instance->_distanceMatrix[i][j] = tmp;
            instance->_distanceMatrix[j][i] = tmp;
        }
    }

    return instance;
}

u_int32_t Instance::getPointsDistance(u_int32_t i, u_int32_t j)
{
	return _distanceMatrix[i][j];
}

dynamic_matrix_t *Instance::getDynamicDistanceMatrix()
{
	dynamic_matrix_t *matrix;

	matrix = new dynamic_matrix_t();
	for (u_int32_t i = 0; i < _size; i++)
	{
		map<u_int32_t, u_int32_t> v;
		for (u_int32_t j = 0; j < _size; j++)
		{
			v[j] = _distanceMatrix[i][j];
		}
		(*matrix)[i] = v;
	}

	return matrix;
}

vertex_dist_t *Instance::getDistanceVector(u_int32_t i)
{
	vertex_dist_t *vect;

	if (i > _size)
		return NULL;

	vect = new vertex_dist_t[_size];
	for (u_int32_t j = 0; j < _size; j++)
	{
		vect[j].vertexId = j;
		vect[j].distance = _distanceMatrix[i][j];
	}

	return vect;
}

int u_int32_compare (const void * a, const void * b)
{
  return ( *(u_int32_t *)a > *(u_int32_t *)b ? 1 : -1 );
}


int vertex_dist_compare (const void * a, const void * b)
{
  return ( ((vertex_dist_t *)a)->distance > ((vertex_dist_t *)b)->distance ? 1 : -1 );
}


u_int32_t Instance::calculateMinLimit()
{
	if (_minLimit == 0)
	{
		u_int32_t *tmpTab = new u_int32_t[_size];
		for (u_int32_t i = 0; i < _size; i++)
		{
			//pomijanie elementu bedacego na przekatnej
			if (i > 0)
				memcpy(tmpTab, _distanceMatrix[i], i * sizeof(u_int32_t));
			if (i < _size - 1)
				memcpy(tmpTab + i, _distanceMatrix[i] + (i + 1), (_size - i - 1) * sizeof(u_int32_t));
			qsort(tmpTab, _size - 1, sizeof(u_int32_t), u_int32_compare);
			_minLimit += tmpTab[0];
		}
		delete tmpTab;
	}

	return _minLimit;
}

Point *Instance::getPoint(u_int32_t i)
{
	return _pointArray[i];
}

u_int32_t Instance::getSize()
{
	return _size;
}

void Instance::saveToFile(string &fileName)
{
	ofstream outputFile(fileName.c_str(), ios::out);
	outputFile << _size << endl;
	for (u_int32_t i = 0; i < _size; i++) {
		for (u_int32_t j = 0; j < _size; j++)
		{
			outputFile << _distanceMatrix[i][j] << " ";
		}
		outputFile << endl;
	}
	outputFile.close();
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
