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

#include <map>
#include <fstream>

using namespace std;

typedef map<u_int32_t, map<u_int32_t, u_int32_t> > dynamic_matrix_t;
typedef struct vertex_dist_
{
	u_int32_t vertexId;
	u_int32_t distance;
} vertex_dist_t;

int vertex_dist_compare (const void * a, const void * b);

class Instance
{
public:
	Instance(u_int32_t size);
	virtual ~Instance();
	u_int32_t getPointsDistance(u_int32_t i, u_int32_t j);
	dynamic_matrix_t *getDynamicDistanceMatrix();
	vertex_dist_t *getDistanceVector(u_int32_t i);

	u_int32_t calculateMinLimit();
	Point *getPoint(u_int32_t i);
	u_int32_t getSize();
	void saveToFile(string &fileName);

	void setName(string name);
	string getName();

	void print();
	static Instance *generateRandomInstance(u_int32_t size, int seed = 0);
	static Instance *loadFromFile(string &fileName);
	static Instance *loadFromFileTSPLib(string &fileName);

private:
	u_int32_t _size;
	u_int32_t _minLimit;
	u_int32_t **_distanceMatrix;
	Point **_pointArray;
	string _name;

	static void readEdges(Instance *instance, ifstream *instanceFile);
};

#endif /* INSTANCE_H_ */
