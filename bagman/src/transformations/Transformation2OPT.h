/*
 * Transformation2OPT.h
 *
 *  Created on: Nov 9, 2010
 *      Author: piekar294
 */

#ifndef TRANSFORMATION2OPT_H_
#define TRANSFORMATION2OPT_H_

#include "Transformation.h"
#include "../heuristics/TSList.h"

class Transformation2OPT: public virtual Transformation {
public:
	Transformation2OPT();
	Transformation2OPT(vector<int> *inVector);
	virtual ~Transformation2OPT();
	virtual bool getNext(vector<int> **outNext);
	virtual void reset(vector<int> *baseVec);

	virtual bool hasNext();
	virtual void moveNext();
	virtual void next(vector<int> **outNext);
	inline  void getNextSwap(TSSwap &ref) { ref.x = _i; ref.y = _j; }

private:
	vector<int> *_base;
	unsigned int _i,_j;
	bool _end;
};

#endif /* TRANSFORMATION2OPT_H_ */
