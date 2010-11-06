/*
 * Point.h
 *
 *  Created on: 2010-10-26
 *      Author: prog
 */

#ifndef POINT_H_
#define POINT_H_

#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "tsp.h"

class Point
{
public:
	Point(u_int32_t x, u_int32_t y);
	void setLabel(std::string &label);
	u_int32_t getX() { return _x; }
	u_int32_t getY() { return _y; }
	void setNum(u_int32_t num) { _num = num; }
	u_int32_t getNum() { return _num; };
	float calcDistance(Point &p);
	static Point *generatePoint(u_int32_t num);
	void print();
	virtual ~Point();

private:
	u_int32_t _x;
	u_int32_t _y;
	u_int32_t _num;
	std::string _label;
};

#endif /* POINT_H_ */
