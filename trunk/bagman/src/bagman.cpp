/*
 * bagman.cpp
 *
 *  Created on: 24-10-2010
 *      Author: qba
 */

#include <vector>
#include <iostream>

// For Get opt
#include <unistd.h>
#include <getopt.h>

#include <string.h>
#include "Generate.h"
#include "heuristics/Calculation.h"
#include "heuristics/RandomCalculation.h"
#include "heuristics/Steepest.h"
#include "heuristics/Greedy.h"
#include "heuristics/Own.h"

#include "bagman.h"

using namespace std;

int iChosenSolution = 0;
int iMaxNumberOfIteretion = 0;


int main(int argc, char **argv) {
	char *caSaveTableFileName = NULL;
	char *caLoadTableFileName = NULL;
	char *caSizeOfTable = NULL;



	int c;
	while (1) {
		//int this_option_optind = optind ? optind : 1;
		int option_index = 0;
		static struct option long_options[] = {
		//					{ "proxy", 1, 0, 0 },
				//					{ "user", 1, 0, 0 },
				//					{ "pass", 1, 0, 0 },
				//					{ "name", 1, 0, 0 },
				//					{ "version", 0, 0, 0 },
				{ "help", 0, 0, 0 }, { 0, 0, 0, 0 } };

		c = getopt_long(argc, argv, "g:l:s:i:tero", long_options, &option_index);
		if (c == -1)
			break;

		switch (c) {
		case 0:
			//				if (!strcmp(long_options[option_index].name, "proxy")) {
			//					if (iProxyType == -1)
			//						iProxyType = CURLPROXY_HTTP;
			//					caProxy = strdup(optarg);
			//					break;
			//				} else if (!strcmp(long_options[option_index].name, "version")) {
			//					printf("chomikuj v. 0.0.1\nauthor:\tthunder\n");
			//					exit(0);
			//				} else
			if (!strcmp(long_options[option_index].name, "help")) {
				cout << "bagman v. 0.0.1" << endl << "author:\tkuba & piekar" << endl << endl;
				cout << "use:" << endl << "\t./bagman [options]" << endl << endl;
				//					printf("\t-u|--user [username]\tGive user to your Chomik.\n");
				//					printf("\t-p|--pass [password]\tGive password to your Chomik.\n");
				//					printf("\t-n|--name [filename]\tGive name if you want to change file name.\n");
				//					printf("\t--proxy [user[:pass]@]IP:port\tSet proxy (if you want).\n");
				//					printf("\t-4\t\t\tUse SOCKS4 as proxy.\n");
				cout << "\t-g [filename]\t\t\tGenerate data for calculation." << endl;
				cout << "\t-s [integer]\t\t\tThe size of generated data." << endl;
				cout << "\t-l [filename]\t\t\tLoad generated date." << endl;
				cout << "\t-r \t\t\tUse random algorithm." << endl;
				cout << "\t-t \t\t\tUse steepest algorithm." << endl;
				cout << "\t-e \t\t\tUse greedy algorithm." << endl;
				cout << "\t-o \t\t\tUse own algorithm." << endl;
				cout << "\t-i \t\t\tNumber of iteration." << endl;
				exit(0);
			} else
				break;
			//				} else if (!strcmp(long_options[option_index].name, "user")) {
			//					caUsername = strdup(optarg);
			//					break;
			//				} else if (!strcmp(long_options[option_index].name, "pass")) {
			//					caPassword = strdup(optarg);
			//					break;
			//				} else if (!strcmp(long_options[option_index].name, "name")) {
			//					caUploadFileName = strdup(optarg);
			//					break;
			//				}
		case 'e':
			iChosenSolution = iChosenSolution | GREEDY;
			break;
		case 'r':
			iChosenSolution = iChosenSolution | RANDOM;
			break;
		case 't':
			iChosenSolution = iChosenSolution | STEEPEST;
			break;
		case 'o':
			iChosenSolution = iChosenSolution | OWNSOLUTION;
			break;
		case 'g':
			caSaveTableFileName = strdup(optarg);
			break;
		case 'l':
			caLoadTableFileName = strdup(optarg);
			break;
		case 's':
			caSizeOfTable = strdup(optarg);
			break;
		case 'i':
			iMaxNumberOfIteretion = atoi(optarg);
			break;
		case '?':
		default:
			break;
		}

	}

	Generate *gen;
	if (caSaveTableFileName != NULL) {
		if (caSizeOfTable != NULL) {
			gen = new Generate(atoi(caSizeOfTable));
			gen->saveTable(string(caSaveTableFileName));
			exit(0);
		} else {
			cerr << "While generating you have to give the size of table as a paramether -s!" << endl;
			exit(1);
		}
	} else if (caLoadTableFileName != NULL) {
		gen = new Generate(string(caLoadTableFileName));
	} else {
		cerr << "You have to load or generate table!" << endl;
		exit(1);
	}

	vector<int> *vec = new vector<int> ();

	for (int i = 0; i < gen->getNumberOfCities(); i++) {
		vec->push_back(i);
	}

	cout << gen->calculateWholeDistance(vec) << endl;

	srand(time(NULL));

	Calculation *calc;

	cout << "Calculating" << endl;
	if ((iChosenSolution & RANDOM) == RANDOM) {
		calc = new RandomCalculation();
		vec = (iMaxNumberOfIteretion) ? calc->solve(gen, iMaxNumberOfIteretion) : calc->solve(gen);
		cout << "Random best solution" << endl;
		cout << gen->calculateWholeDistance(vec) << endl;
		gen->DEBUG_printTrace(vec);
		delete calc;
	}
	if ((iChosenSolution & STEEPEST) == STEEPEST) {
		calc = new Steepest();
		vec = (iMaxNumberOfIteretion) ? calc->solve(gen, iMaxNumberOfIteretion) : calc->solve(gen);
		cout << "Steepest best solution" << endl;
		cout << gen->calculateWholeDistance(vec) << endl;
		gen->DEBUG_printTrace(vec);
		delete calc;
	}
	if ((iChosenSolution & GREEDY) == GREEDY) {
		calc = new Greedy();
		vec = (iMaxNumberOfIteretion) ? calc->solve(gen, iMaxNumberOfIteretion) : calc->solve(gen);
		cout << "Greedy best solution" << endl;
		cout << gen->calculateWholeDistance(vec) << endl;
		gen->DEBUG_printTrace(vec);
		delete calc;
	}
	if ((iChosenSolution & OWNSOLUTION) == OWNSOLUTION) {
		calc = new Own();
		vec = (iMaxNumberOfIteretion) ? calc->solve(gen, iMaxNumberOfIteretion) : calc->solve(gen);
		cout << "Own best solution" << endl;
		cout << gen->calculateWholeDistance(vec) << endl;
		gen->DEBUG_printTrace(vec);
		delete calc;
	}

	delete gen;

	return 0;
}
