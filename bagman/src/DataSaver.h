/*
 * DataSaver.h
 *
 *  Created on: Nov 4, 2010
 *      Author: piekar294
 */

#ifndef DATASAVER_H_
#define DATASAVER_H_

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class DataSaver {
public:
	DataSaver(string pstrFName, ios_base::openmode pMode = ios_base::out|ios_base::trunc);
	virtual ~DataSaver();

	/**
	 * Used to save time/score results.
	 */
	static DataSaver* GetTimeFile(string pstrFName);

	/**
	 * Used to save time/score results.
	 */
	static DataSaver* GetSolutionFile(string pstrFName);

	/**
	 * Used to save iteration/score results.
	 */
	static DataSaver* GetIterationFile(string pstrFName);

	/**
	 * Used to save no_of_steps/score results.
	 */
	static DataSaver* GetOverallFile(string pstrFName);


	inline void open() {
		_WorkingFile.open(_FileName.c_str(), ios_base::out|ios_base::app);
	}

	inline void close() {
		_WorkingFile.close();
	}

	void saveLine(double pdTime, long plScore);

	void saveLine(int piStamp, long plScore);

	void saveLine(string strAlgorithm, vector<int> *solution);

	void saveOverallLine(string pstrFName, double pdTime, int piSteps, int piSeenS, int score);

private:

	ofstream _WorkingFile;
	string _FileName;

	/**
	 * Insert:
	 * "#iteration #score"
	 * columns to a result file.
	 */
	void insIterationTempate();

	/**
	 * Insert:
	 * "#time #score"
	 * columns to a result file.
	 */
	void insTimeTempate();

};

#endif /* DATASAVER_H_ */
