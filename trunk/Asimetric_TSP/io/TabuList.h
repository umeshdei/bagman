/*
 * TabuList.h
 *
 *  Created on: 2010-11-27
 *      Author: kolczak
 */

#ifndef TABULIST_H_
#define TABULIST_H_

#define DEFAULT_TABU_SIZE 20

#include <list>
#include "Point.h"
#include <iostream>

using namespace std;

class TabuList {
public:
	TabuList(u_int32_t size = DEFAULT_TABU_SIZE);
	virtual ~TabuList();
	void addToList(Point *p);
	bool isInTabu(Point *p);
private:
	std::list<Point*> *_tsList;
	u_int32_t _tsListSize;
};

#endif /* TABULIST_H_ */
