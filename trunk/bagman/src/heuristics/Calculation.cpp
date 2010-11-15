/*
 * Calculation.cpp
 *
 *  Created on: 11-11-2010
 *      Author: qba
 */

#include "Calculation.h"

Calculation::Calculation(string strFileName) {
	_ovallSaver = DataSaver::GetOverallFile(strFileName + ".all");
}

Calculation::Calculation() {

	_ovallSaver = NULL;
}

Calculation::~Calculation() {
	if (_ovallSaver != NULL)
		delete _ovallSaver;
}
