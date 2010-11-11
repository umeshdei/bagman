/*
 * Transformation.h
 *
 *  Created on: Nov 9, 2010
 *      Author: piekar294
 */

#ifndef TRANSFORMATION_H_
#define TRANSFORMATION_H_

#include <vector>

using namespace std;

class Transformation {
public:
	virtual bool getNext(vector<int> **outNext) = 0;
	virtual void reset(vector<int> *baseVec) = 0;
};

#endif /* TRANSFORMATION_H_ */
