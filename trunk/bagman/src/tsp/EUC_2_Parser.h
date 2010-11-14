/*
 * EUC_2_Parser.h
 *
 *  Created on: Nov 13, 2010
 *      Author: piekar294
 */

#ifndef EUC_2_PARSER_H_
#define EUC_2_PARSER_H_

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <vector>
#include "../Point.h"

using namespace std;

class EUC_2_Parser {
public:
	EUC_2_Parser();
	virtual ~EUC_2_Parser();

	bool parse(string pstrFile, vector<Point*> *cord);
};

#endif /* EUC_2_PARSER_H_ */
