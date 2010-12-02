/*
 * Point.h
 *
 *  Created on: 25-10-2010
 *      Author: qba
 */

#ifndef POINT_H_
#define POINT_H_

#include <stdlib.h>
#include <math.h>

class Point {
public:
	Point(int piX, int piY);
	static Point *generateRandomPoint(int piMaxX, int piMaxY);
	static int getDistanceBetweenPoints(Point *pptFirstPoint, Point *pptSecondPoint);
	int getDistanceFromPoint(Point *pptPoint);
	virtual ~Point();
	int getX();
	int getY();

	int operator==(Point &cmp) {return (cmp._iX == this->_iX) && (cmp._iY == this->_iY);}
private:
	Point();
	void setX(int piX);
	void setY(int piY);
	int _iX;
	int _iY;
};

#endif /* POINT_H_ */
