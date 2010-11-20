/*
 * TSPDataSaver.h
 *
 *  Created on: 2010-11-18
 *      Author: kolczak
 */
#ifndef TSPDATASAVER_H_
#define TSPDATASAVER_H_

#include "Instance.h"

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

class TSPDataSaver {
public:
	virtual ~TSPDataSaver();
	TSPDataSaver(string pstrAlgName, Instance* pInstance, ios_base::openmode pMode = ios_base::in
				| ios_base::trunc);
	void saveLine(string line);

private:
	ofstream _WorkingFile;
	string _FileName;

	bool checkIfExist(string *pstrFName);
	bool fexists(const char *filename);
};

#endif /* TSPDATASAVER_H_ */
