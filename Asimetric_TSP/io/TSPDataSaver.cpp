/*
 * TSPDataSaver.cpp
 *
 *  Created on: 2010-11-18
 *      Author: kolczak
 */

#include "TSPDataSaver.h"

bool TSPDataSaver::fexists(const char *filename)
{
  ifstream ifile(filename);
  return ifile;
}

bool TSPDataSaver::checkIfExist(string *pstrFName)
{
	int suffix = 0;
	if(fexists(pstrFName->c_str()))
	{	//plik istnieje
		size_t underline = pstrFName->rfind('_');
		int len = pstrFName->length();

		string number = *pstrFName;
		number.erase(0, underline+1);
		//cout << number << endl;
		suffix = atoi(number.c_str());
		suffix ++;

		//cout << "mam sufiks: " << suffix << endl;
		pstrFName->erase(underline, len);
		pstrFName->append("_");
		std::stringstream out;
		out << suffix;
		pstrFName->append(out.str());

		return true;
	}
	return false;
}

TSPDataSaver::TSPDataSaver(string pstrAlgName, Instance* pInstance, ios_base::openmode pMode) {
	string fName;
	fName = "out/";
	fName.append(pstrAlgName);
	fName.append("_");
	std::stringstream out;
	out << pInstance->getSize();
	fName.append(out.str());
	fName.append("_");

	//wytnij tylko nazwe pliku zrodlowego bez sciezki
	string instanceName = pInstance->getName();
	int slashPlace = instanceName.rfind('/');
	//cout << "slash: " << slashPlace << "w stringu: " << instanceName << endl;
	if (slashPlace != -1)
		instanceName.erase(0, slashPlace+1);
	fName.append(instanceName);

	fName.append("_0");
	while(checkIfExist(&fName));
	_FileName = fName;
	_WorkingFile.open(fName.c_str(), pMode);
	//_WorkingFile.setf(ios::left);
	//cout << "tworze plik do zapisu: " << fName << endl;
}

void TSPDataSaver::saveLine(string line)
{
	//cout << "wypisuje: " << line << endl;
	_WorkingFile << line << endl;
}

TSPDataSaver::~TSPDataSaver() {
	if(_WorkingFile.is_open())
	{
		//_WorkingFile << endf;
		_WorkingFile.close();
	}
	// TODO Auto-generated destructor stub
}
