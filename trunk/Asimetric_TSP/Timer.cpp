/*
 * Timer.cpp
 *
 *  Created on: Nov 11, 2010
 *      Author: piekar294
 */

#include "Timer.h"

Timer::Timer()
{

}

Timer::~Timer()
{

}

void Timer::start()
{
	this->_start = clock();
}

double Timer::getRunTime()
{
	clock_t final = clock() - _start;
	return (double) final / ((double) CLOCKS_PER_SEC);
}
