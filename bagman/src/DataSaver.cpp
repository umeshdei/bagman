/*
 * DataSaver.cpp
 *
 *  Created on: Nov 4, 2010
 *      Author: piekar294
 */

#include "DataSaver.h"

DataSaver::DataSaver(string pstrFName, ios_base::openmode pMode) {
	_FileName = pstrFName;
	_WorkingFile.open(pstrFName.c_str(), pMode);
	//_WorkingFile.setf(ios::left);

	//TODO:odczaic jak duze to ustawic :)
	//_WorkingFile.width(20);
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

void DataSaver::saveLine(string strAlgorithm, vector<int> *solution) {
	_WorkingFile << strAlgorithm << "\t";
	for (unsigned int i = 0; i < solution->size(); i++)
		_WorkingFile << (*solution)[i] << "\t";
	_WorkingFile << std::endl;
}

void DataSaver::saveOverallLine(string pstrFName, double pdTime, int piSteps, int piSeenS, int score) {
	_WorkingFile << fixed << pstrFName << "\t" << pdTime << "\t" << piSteps << "\t" << piSeenS << "\t" << score << std::endl;
}

DataSaver* DataSaver::GetIterationFile(string pstrFName) {
	DataSaver *result = new DataSaver(pstrFName, ios_base::out|ios_base::app);
	//result->insIterationTempate();

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

DataSaver* DataSaver::GetOverallFile(string pstrFName) {
	DataSaver *result = new DataSaver(pstrFName, ios_base::out|ios_base::app);

	return result;
}

void DataSaver::insIterationTempate() {
	_WorkingFile << "#iteration\t#score" << std::endl;
}

void DataSaver::insTimeTempate() {
	_WorkingFile << "#time\t#score" << std::endl;
}
