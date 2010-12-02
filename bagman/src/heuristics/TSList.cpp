/*
 * TSList.cpp
 *
 *  Created on: Nov 30, 2010
 *      Author: piekar294
 */

#include "TSList.h"

TSList::TSList(int tabuSize): _tabuSize(tabuSize) {
}

TSList::~TSList() {
	//clear tabu list
	for (list<TSSwap*>::iterator it = _container.begin(); it != _container.end(); it++) {
		delete *it;
	}
	_container.clear();
}

void TSList::update(TSSwap *move) {
	if (_container.size() == _tabuSize) {
		TSSwap* tmp = _container.front();
		delete tmp;
		_container.pop_front();
	}
	_container.push_back(move);
}

bool TSList::checkMove(TSSwap *move) {
	//if tabu list contains move return false
	for( list<TSSwap*>::iterator it = _container.begin(); it != _container.end(); it++) {
		if ( *(*it) == *move) {
			return false;
		}
	}

	return true;
}

bool TSList::checkMove(int x, int y) {
	TSSwap tmp(x,y);
	return this->checkMove(&tmp);
}
