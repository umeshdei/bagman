/*
 * TSList.h
 *
 *  Created on: Nov 30, 2010
 *      Author: piekar294
 */

#ifndef TSLIST_H_
#define TSLIST_H_

#include <list>
#include "../Point.h"

using namespace std;

typedef struct TSSwap {
	int x;
	int y;

	TSSwap() {}
	TSSwap(int x, int y): x(x), y(y){}
	int operator==(TSSwap &ref) {
		return ((x == ref.x && y == ref.y) || (x == ref.y && y == ref.x));
	}
} TSSwap;

class TSList {
public:
	TSList(int tabuSize);
	virtual ~TSList();
	void update(TSSwap *move);

	// true if move is possible (do not exist on tabu list)
	bool checkMove(TSSwap *move);
	bool checkMove(int x, int y);
	//void update(TSSwap *move)

private:
	list<TSSwap*> _container;
	unsigned int _tabuSize;
};

#endif /* TSLIST_H_ */
