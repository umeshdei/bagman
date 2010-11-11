/*
 * Transformation2OPT.cpp
 *
 *  Created on: Nov 9, 2010
 *      Author: piekar294
 */

#include "Transformation2OPT.h"

Transformation2OPT::Transformation2OPT() {
}

Transformation2OPT::Transformation2OPT(vector<int> *inVector) {
	this->reset(inVector);
}

Transformation2OPT::~Transformation2OPT() {
	if (_base != NULL) {
		delete _base;
	}
}

bool Transformation2OPT::getNext(vector<int> **outNext) {
	if (_end) {
		outNext = NULL;
		return false;
	}

	//first swap
	*outNext = new vector<int>(*_base);
	int tmp;
	tmp = (*outNext)->at(_i);
	(**outNext)[_i] = (**outNext)[_j];
	(**outNext)[_j] = tmp;

	//iterate to next result
    if (++_j == _base->size()) {
    	if (++_i == (_base->size()-1)) {
			_end = true;
    	}
    	_j = _i + 1;
    }

	return true;
}

void Transformation2OPT::reset(vector<int> *baseVec) {
	_i = 0;
	_j = 0;
	_end = false;
	if (_base != NULL) {
		delete _base;
	}
	_base = new vector<int>(*baseVec);
}
