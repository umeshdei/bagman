/*
 * Point.cpp
 *
 *  Created on: 2010-10-26
 *      Author: prog
 */

#include "Point.h"

Point::Point(u_int32_t x, u_int32_t y) : _x(x), _y(y)
{
}

void Point::setLabel(std::string &label)
{
	_label = std::string(label);
}

void Point::print()
{
	printf("Point(%u, %u) - %s\n", _x, _y, _label.c_str());
}

float Point::calcDistance(Point &p)
{
	return sqrt((_x - p.getX()) * (_x - p.getX()) + (_y - p.getY()) * (_y - p.getY()));
}

Point *Point::generatePoint(u_int32_t num)
{
	u_int32_t x, y;
	Point *p;

	x = rand() % TSP_RAND_MAX + 1;
	y = rand() % TSP_RAND_MAX + 1;

	p = new Point(x, y);
	p->setNum(num);
	return p;
}

Point *Point::createNoCoordinatePoint(u_int32_t num)
{
	u_int32_t x, y;
	Point *p;

	x = -1;
	y = -1;

	p = new Point(x, y);
	p->setNum(num);
	return p;
}

Point::~Point()
{
}
