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
#include "heuristics/Tabu.h"
#include "heuristics/SA.h"

#include "bagman.h"
#include "tsp/tsplib.h"
#include "tsp/EUC_2_Parser.h"

using namespace std;

int iChosenSolution = -1;
int iMaxNumberOfIteretion = 0;
bool DEBUG = false;

char *strjoin(char *c1, char* c2) {
	char *ret = new char[strlen(c1) + strlen(c2) +1];
	strcpy(ret, c1);
	strcpy(ret + strlen(c1), c2);
	ret[strlen(c1) + strlen(c2)] = '\0';
	return ret;
}

int main(int argc, char **argv) {
	char *caSaveFileName = NULL;
	char *caLoadTableFileName = NULL;
	char *caSizeOfTable = NULL;
	bool bGenerate = false;
	bool bTspFile = false;

	//PRZYKLAD WYKORZYSTANIA EUC_2_PARSER
	/*
	EUC_2_Parser ep;
	vector<Point*> cord;

	cout << ep.parse("/home/piekar294/Downloads/tmp/tsp/euc_2d/a280.tsp", &cord)<< endl;
	for(unsigned int i=0; i < cord.size(); i++) {
		cout << i+1 << "\t" << (cord[i])->getX() << "\t" << (cord[i])->getY() << endl;
	}

	Generate ggg(&cord);
	cout <<"przeszlo generate" <<endl;
	return 0;
    */

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

		c = getopt_long(argc, argv, "gl:s:i:teabrpo:dw", long_options, &option_index);
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
				cout << "\t-g \t\t\tGenerate data for calculation." << endl;
				cout << "\t-p \t\t\tUse tsp file as input." << endl;
				cout << "\t-s [integer]\t\t\tThe size of generated data." << endl;
				cout << "\t-l [filename]\t\t\tLoad generated date." << endl;
				cout << "\t-o [filename]\t\t\tOutput date." << endl;
				cout << "\t-r \t\t\tUse random algorithm." << endl;
				cout << "\t-t \t\t\tUse steepest algorithm." << endl;
				cout << "\t-e \t\t\tUse greedy algorithm." << endl;
				cout << "\t-w \t\t\tUse own algorithm." << endl;
				cout << "\t-a \t\t\tUse SA- algorithm." << endl;
				cout << "\t-b \t\t\tUse SA- algorithm." << endl;
				cout << "\t-i \t\t\tNumber of iteration." << endl;
				cout << "\t-d \t\t\tPrint debug." << endl;
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
		case 'p':
			bTspFile = true;
			break;
		case 'e':
			if (iChosenSolution != -1) {
				cerr << "You can choose only one algorithm!" << endl;
				exit(1);
			}
			iChosenSolution = GREEDY;
			break;
		case 'r':
			if (iChosenSolution != -1) {
				cerr << "You can choose only one algorithm!" << endl;
				exit(1);
			}
			iChosenSolution = RANDOM;
			break;
		case 't':
			if (iChosenSolution != -1) {
				cerr << "You can choose only one algorithm!" << endl;
				exit(1);
			}
			iChosenSolution = STEEPEST;
			break;
		case 'w':
			if (iChosenSolution != -1) {
				cerr << "You can choose only one algorithm!" << endl;
				exit(1);
			}
			iChosenSolution = OWNSOLUTION;
			break;
		case 'a':
			if (iChosenSolution != -1) {
				cerr << "You can choose only one algorithm!" << endl;
				exit(1);
			}
			iChosenSolution = SA_;
			break;
		case 'b':
			if (iChosenSolution != -1) {
				cerr << "You can choose only one algorithm!" << endl;
				exit(1);
			}
			iChosenSolution = TABU;
			break;
		case 'o':
			caSaveFileName = strdup(optarg);
			break;
		case 'g':
			bGenerate = true;
			break;
		case 'l':
			caLoadTableFileName = strdup(optarg);
			break;
		case 's':
			caSizeOfTable = strdup(optarg);
			break;
		case 'd':
			DEBUG = true;
			break;
		case 'i':
			iMaxNumberOfIteretion = atoi(optarg);
			break;
		case '?':
		default:
			break;
		}

	}

	if (caSaveFileName == NULL) {
		cerr << "You have to give the output file name as a parameter -o!" << endl;
		exit(1);
	}

	if (iChosenSolution == -1) {
		cerr << "You have to choose one algorithm!" << endl;
		exit(1);
	}

	Generate *gen;
	if (bGenerate) {
		if (caSizeOfTable != NULL) {
			gen = new Generate(atoi(caSizeOfTable));
			gen->saveTable(string(caSaveFileName));
			exit(0);
		} else {
			cerr << "While generating you have to give the size of table as a parameter -s!" << endl;
			exit(1);
		}
	} else if (caLoadTableFileName != NULL) {
		if (bTspFile) {
			vector<Point *> *coord = new vector<Point *>();
			EUC_2_Parser ep;

			ep.parse(caLoadTableFileName, coord);

			gen = new Generate(coord);
			cout << "Loaded" << endl;
		}
		else
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
	if (iChosenSolution != SA_) {
	Calculation *calc;

	switch (iChosenSolution) {
	case GREEDY:
			calc = new Greedy(caSaveFileName);
			break;
	case OWNSOLUTION:
			calc = new Own(caSaveFileName);
			break;
	case STEEPEST:
			calc = new Steepest(caSaveFileName);
			break;
	case RANDOM:
			calc = new RandomCalculation(caSaveFileName);
			break;
	case TABU:
			calc = new Tabu((unsigned int)(gen->getNumberOfCities() / 10),  70, iMaxNumberOfIteretion, caSaveFileName);
			break;
	default:
		cerr << "Internal ERROR! Unknown algorithm!" << endl;
		exit(1);
	}


	vec = (iMaxNumberOfIteretion) ? calc->solve(gen, iMaxNumberOfIteretion, caLoadTableFileName) : calc->solve(gen, caLoadTableFileName);
	//delete calc;

	}
	else
	{
		SA *s = new SA();
		s->solve(gen, caLoadTableFileName, iMaxNumberOfIteretion, 0.95, caSaveFileName);
		//delete s;
		//s = new SA();
		//s->solve(gen, strjoin(caLoadTableFileName, ".95"), iMaxNumberOfIteretion, 0.95, strjoin(caSaveFileName,".99"));
		//delete s;
	}
	if (DEBUG)
		gen->DEBUG_printTrace(vec);
	cout << "Best known solution: " << gen->calculateWholeDistance(vec) << endl;

	//delete gen;

	return 0;
}
