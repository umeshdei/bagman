/*
 * Transformation2OPT.h
 *
 *  Created on: Nov 9, 2010
 *      Author: piekar294
 */

#ifndef TRANSFORMATION2OPT_H_
#define TRANSFORMATION2OPT_H_

#include "Transformation.h"

class Transformation2OPT: public virtual Transformation {
public:
	Transformation2OPT();
	Transformation2OPT(vector<int> *inVector);
	virtual ~Transformation2OPT();
	virtual bool getNext(vector<int> *outNext);
	virtual void reset(vector<int> *baseVec);

private:
	vector<int> *_base;
	unsigned int _i,_j;
	bool _end;
};

#endif /* TRANSFORMATION2OPT_H_ */
