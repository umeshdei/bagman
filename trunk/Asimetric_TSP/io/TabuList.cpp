/*
 * TabuList.cpp
 *
 *  Created on: 2010-11-27
 *      Author: kolczak
 */

#include "TabuList.h"

TabuList::TabuList() {
	_tsList = new std::list<Point*>();
	_tsListSize = TABU_SIZE;
	// TODO Auto-generated constructor stub

}

void TabuList::addToList(Point *p) {
	Point* newPoint;

	//usun najstarszy element
	if(_tsList->size() >= _tsListSize) {
		Point* oldest;
		oldest = _tsList->front();
		_tsList->pop_front();
		delete oldest;
	}

	newPoint = new Point(*p);
	_tsList->push_back(newPoint);
}

bool TabuList::isInTabu(Point* p) {
	std::list<Point*>::iterator it;
	it = _tsList->begin();
	for (; it != _tsList->end(); it++)
	{
		if (((*it)->getX() == p->getX()) && ((*it)->getY() == p->getY()))
			return true;
		else if (((*it)->getX() == p->getY()) && ((*it)->getY() == p->getX()))
			return true;
	}

	return false;
}

TabuList::~TabuList() {
	delete _tsList;
	// TODO Auto-generated destructor stub
}
