/*
 * Point.cpp
 *
 *  Created on: 25-10-2010
 *      Author: qba
 */

#include "Point.h"

Point::Point(int piX, int piY) {
	_iX = piX;
	_iY = piY;
}

Point *Point::generateRandomPoint(int piMaxX, int piMaxY) {
	Point *ptReturn = new Point();
	ptReturn->setX(rand() % piMaxX);
	ptReturn->setY(rand() % piMaxY);
	return ptReturn;
}

int Point::getDistanceBetweenPoints(Point *pptFirstPoint, Point *pptSecondPoint) {
	int iReturnValue;
	int iDiffX = abs(pptFirstPoint->getX() - pptSecondPoint->getX());
	int iDiffY = abs(pptFirstPoint->getY() - pptSecondPoint->getY());
	iReturnValue = (int) sqrt (iDiffX * iDiffX + iDiffY * iDiffY);
	return iReturnValue;
}

int Point::getDistanceFromPoint(Point *pptPoint) {
	return Point::getDistanceBetweenPoints(this, pptPoint);
}

Point::Point() {
}

Point::~Point() {
}


void Point::setX(int piX) {
	_iX = piX;
}
void Point::setY(int piY) {
	_iY = piY;
}


int Point::getX() {
	return _iX;
}
int Point::getY() {
	return _iY;
}
