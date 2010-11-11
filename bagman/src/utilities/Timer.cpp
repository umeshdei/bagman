/*
 * Timer.cpp
 *
 *  Created on: Nov 11, 2010
 *      Author: piekar294
 */

#include "Timer.h"

Timer::Timer() {
	// TODO Auto-generated constructor stub

}

Timer::~Timer() {
	// TODO Auto-generated destructor stub
}

void Timer::start() {
	this->_start = clock();
}

double Timer::getRunTime() {
	clock_t final = clock() - _start;
	return (double)final / ((double)CLOCKS_PER_SEC);
}
