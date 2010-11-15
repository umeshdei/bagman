/*
 * Calculation.cpp
 *
 *  Created on: 11-11-2010
 *      Author: qba
 */

#include "Calculation.h"

Calculation::Calculation(string strTimeFileName, string strIterationFileName, string strStepFileName) {
	_timeSaver = DataSaver::GetTimeFile(strTimeFileName);
	_iteretionSaver = DataSaver::GetIterationFile(strIterationFileName);
	_ovallSaver = DataSaver::GetOverallFile(strStepFileName);
}

Calculation::Calculation(string strFileName) {
	_timeSaver = DataSaver::GetTimeFile(strFileName + "_time");
	_iteretionSaver = DataSaver::GetTimeFile(strFileName + "_iter");
	_ovallSaver = DataSaver::GetTimeFile(strFileName + "_step");
}

Calculation::Calculation() {
	_timeSaver = NULL;
	_iteretionSaver = NULL;
	_ovallSaver = NULL;
}

Calculation::~Calculation() {
	if (_timeSaver != NULL)
		delete _timeSaver;
	if (_iteretionSaver != NULL)
		delete _iteretionSaver;
	if (_ovallSaver != NULL)
		delete _ovallSaver;
}
