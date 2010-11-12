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
	_stepSaver = DataSaver::GetStepsFile(strStepFileName);
}

Calculation::Calculation(string strFileName) {
	_timeSaver = DataSaver::GetTimeFile(strFileName + "_time");
	_iteretionSaver = DataSaver::GetTimeFile(strFileName + "_iter");
	_stepSaver = DataSaver::GetTimeFile(strFileName + "_step");
}

Calculation::Calculation() {

}

Calculation::~Calculation() {
	delete _timeSaver;
	delete _iteretionSaver;
	delete _stepSaver;
}
