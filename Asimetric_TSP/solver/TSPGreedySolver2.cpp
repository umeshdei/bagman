/*
 * TSPGreedySolver2.cpp
 *
 *  Created on: 2010-11-06
 *      Author: prog
 */

#include "TSPGreedySolver2.h"

TSPGreedySolver2::TSPGreedySolver2(Instance *instance)
{
	_instance = instance;
	saver = new TSPDataSaver("greedy2", instance);
}

Result *TSPGreedySolver2::solve()
{
	Result *best;
	u_int32_t lastId;
	set<u_int32_t> usedVertices;
	vertex_dist_t *vect;

	best = new Result();
	lastId = rand() % _instance->getSize();

	for (u_int32_t i = 0; i < _instance->getSize(); i++)
	{
		vect = _instance->getDistanceVector(lastId);
		if (vect == NULL)
		{
			delete best;
			return NULL;
		}
		qsort(vect, _instance->getSize(), sizeof(vertex_dist_t), vertex_dist_compare);
		for (u_int32_t j = 0; j < _instance->getSize(); j++)
		{
			if (usedVertices.count(vect[j].vertexId) == 0 && vect[j].vertexId != i)
			{
				best->push_back(_instance->getPoint(vect[j].vertexId));
				usedVertices.insert(vect[j].vertexId);
				lastId = vect[j].vertexId;
				break;
			}
		}
		u_int32_t a = i%(u_int32_t)FREQUENCY_SAVER;
		//cout << a << endl;
		if(a == 0)
		{
			std::stringstream out;
			out << i;
			out << " ";
			out << best->getCalculatedDistance();
			saver->saveLine(out.str());
		}
	}
	best->setCalculatedDistance(calculateDistance(best));

	return best;
}

TSPGreedySolver2::~TSPGreedySolver2()
{
	delete saver;
}
