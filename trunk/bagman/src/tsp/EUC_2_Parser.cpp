/*
 * EUC_2_Parser.cpp
 *
 *  Created on: Nov 13, 2010
 *      Author: piekar294
 */

#include "EUC_2_Parser.h"

EUC_2_Parser::EUC_2_Parser() {
	// TODO Auto-generated constructor stub

}

EUC_2_Parser::~EUC_2_Parser() {
	// TODO Auto-generated destructor stub
}

bool EUC_2_Parser::parse(string pstrFile, vector<Point*> *cord) {
	ifstream ifs;
	string line;
	int size;


	ifs.open(pstrFile.c_str(), ios_base::in);

	if (!ifs.good()) {
		return false;
	}

	while (getline(ifs, line)) {
		if (line.compare(0, strlen("DIMENSION"),"DIMENSION") == 0) {
			sscanf(line.c_str(), "DIMENSION%*s %d", &size);
			break;
		}
	}
	if (ifs.eof())
		return false;

	while (getline(ifs, line)) {
		if (line.compare(0, strlen("NODE_COORD_SECTION"),"NODE_COORD_SECTION") == 0) {
			sscanf(line.c_str(), "DIMENSION%*s %d", &size);
			break;
		}
	}
	if (ifs.eof())
		return false;

	int i, x, y;

	while (getline(ifs, line)) {
		sscanf(line.c_str(), "%d %d %d", &i, &x, &y );
		cord->push_back(new Point(x,y));
		if (i == size) {
			break;
		}
	}

	return true;
}
