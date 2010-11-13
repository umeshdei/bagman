/*
 * DataSaver.cpp
 *
 *  Created on: Nov 4, 2010
 *      Author: piekar294
 */

#include "DataSaver.h"

DataSaver::DataSaver(string pstrFName) {
	_FileName = pstrFName;
	_WorkingFile.open(pstrFName.c_str(), ios_base::out|ios_base::trunc);
	_WorkingFile.setf(ios::left);

	//TODO:odczaic jak duze to ustawic :)
	_WorkingFile.width(20);
	_WorkingFile.precision(2);
}

DataSaver::~DataSaver() {
	if (_WorkingFile.is_open()) {
		_WorkingFile.close();
	}
}

void DataSaver::saveLine(double pdTime, long plScore) {
	_WorkingFile << fixed << pdTime << "\t" << plScore << std::endl;
}

void DataSaver::saveLine(int piStamp, long plScore) {
	_WorkingFile << piStamp << "\t" << plScore << std::endl;
}

void DataSaver::saveLine(vector<int> *solution) {
	for (unsigned int i = 0; i < solution->size(); i++)
		_WorkingFile << (*solution)[i] << "\t";
}

DataSaver* DataSaver::GetIterationFile(string pstrFName) {
	DataSaver *result = new DataSaver(pstrFName);
	result->insIterationTempate();

	return result;
}

DataSaver* DataSaver::GetSolutionFile(string pstrFName) {
	DataSaver *result = new DataSaver(pstrFName);

	return result;
}

DataSaver* DataSaver::GetTimeFile(string pstrFName) {
	DataSaver *result = new DataSaver(pstrFName);
	result->insTimeTempate();

	return result;
}

DataSaver* DataSaver::GetStepsFile(string pstrFName) {
	DataSaver *result = new DataSaver(pstrFName);
	result->insStepsTempate();

	return result;
}

void DataSaver::insIterationTempate() {
	_WorkingFile << "#iteration\t#score" << std::endl;
}

void DataSaver::insTimeTempate() {
	_WorkingFile << "#time\t#score" << std::endl;
}

void DataSaver::insStepsTempate() {
	_WorkingFile << "#no_of_steps\t#score" << std::endl;
}
