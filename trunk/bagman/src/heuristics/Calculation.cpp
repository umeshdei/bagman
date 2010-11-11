/*
 * Calculation.cpp
 *
 *  Created on: 11-11-2010
 *      Author: qba
 */

#include "Calculation.h"

Calculation::Calculation(string strOutputFileName) : outputStream(strOutputFileName.c_str(), ios::out) {
	//ifstream tmp(strOutputFileName.c_str());
	//outputStream = tmp;
}
