/*
 * Timer.h
 *
 *  Created on: Nov 11, 2010
 *      Author: piekar294
 */

#ifndef TIMER_H_
#define TIMER_H_

#include <time.h>

class Timer {
public:
	Timer();
	virtual ~Timer();
	void start();
	double getRunTime();

private:
	clock_t _start;
};

#endif /* TIMER_H_ */
