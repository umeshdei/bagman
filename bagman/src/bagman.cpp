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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <math.h>

/* ========================================================================== */
/* Types */

typedef
unsigned int
(*distance_func_type)
	(struct tsplib_node_coord_struct a,
	 struct tsplib_node_coord_struct b);

/* ========================================================================== */
/* Local Prototypes */

static
unsigned int
euc_2d_distance_func
	(struct tsplib_node_coord_struct a,
	 struct tsplib_node_coord_struct b);

static
unsigned int
geom_distance_func
	(struct tsplib_node_coord_struct a,
	 struct tsplib_node_coord_struct b);


/* ========================================================================== */
/* Functions */

/* ================================== */
/* Lifecycle Functions */

struct tsplib_tsp_struct *
tsplib_tsp_new
	(char *name,
	 size_t name_len,
	 unsigned int dimension,
	 tsplib_edge_weight_type edge_weight_type)
{
	struct tsplib_tsp_struct *tsp;

	tsp = (struct tsplib_tsp_struct *)malloc(sizeof *tsp);

	tsp->name = (char *)malloc(name_len + 1);
	strncpy(tsp->name, name, name_len);
	tsp->name[name_len] = '\0';

	tsp->comments = (char **)malloc(sizeof *tsp->comments);
	tsp->comments[0] = NULL;

	tsp->dimension = dimension;

	tsp->edge_weight_type = edge_weight_type;

	tsp->node_coords = (struct tsplib_node_coord_struct*) calloc \
		(sizeof *tsp->node_coords,
		 dimension);

	tsp->distance_map = NULL;

	return tsp;
}

void
tsplib_tsp_free
	(struct tsplib_tsp_struct *tsp)
{
	int j;

	if (tsp->distance_map) {
		free(tsp->distance_map);
	}
	free(tsp->node_coords);

	for (j = 0; tsp->comments[j]; j++) {
		free(tsp->comments[j]);
	}
	free(tsp->comments);

	free(tsp->name);

	free(tsp);
}

tsplib_edge_weight_type
tsplib_str_to_edge_weight_type
	(char *type_str,
	 size_t type_str_len)
{
	int j;

	for (j = 0; tsplib_edge_weight_type_strings[j].str; j++) {
		if (tsplib_edge_weight_type_strings[j].len == type_str_len) {
			if (!strncmp \
				(tsplib_edge_weight_type_strings[j].str,
				 type_str,
				 type_str_len)) {

				return tsplib_edge_weight_type_strings[j].type;
			}

		}
	}
	return tsplib_edge_weight_type_strings[j].type;

}

/* ================================== */
/* Distance Functions */

static
unsigned int
euc_2d_distance_func
	(struct tsplib_node_coord_struct a,
	 struct tsplib_node_coord_struct b)
{
	double xd, yd;
	xd = b.x - a.x;
	yd = b.y - a.y;

	return (unsigned int) sqrt(xd * xd + yd * yd);
}

#undef M_PI
#define M_PI 3.14159265358979323846264
static
unsigned int
geom_distance_func
	(struct tsplib_node_coord_struct a,
	 struct tsplib_node_coord_struct b)
{
     double lati, latj, longi, longj;
     double q1, q2, q3, q4, q5;
     lati = M_PI * a.x / 180.0;
     latj = M_PI * b.x / 180.0;
     longi = M_PI * a.y / 180.0;
     longj = M_PI * b.y / 180.0;
     q1 = cos (latj) * sin(longi - longj);
     q3 = sin((longi - longj)/2.0);
     q4 = cos((longi - longj)/2.0);
     q2 = sin(lati + latj) * q3 * q3 - sin(lati - latj) * q4 * q4;
     q5 = cos(lati - latj) * q4 * q4 - cos(lati + latj) * q3 * q3;
     return (unsigned int) (6378388.0 * atan2(sqrt(q1*q1 + q2*q2), q5) + 1.0);
}


void
tsplib_tsp_construct_distance_map
	(struct tsplib_tsp_struct *tsp)
{
	unsigned int j, k, s, dimension;
	unsigned int *distance_map;

	struct tsplib_node_coord_struct *node_coords;
	distance_func_type distance_func;

	node_coords = tsp->node_coords;
	dimension = tsp->dimension;

	if (tsp->distance_map) {
		free(tsp->distance_map);
		tsp->distance_map = NULL;
	}

	distance_map = (unsigned int *) calloc \
		(sizeof *distance_map,
		 (dimension - 1) * dimension / 2.0);

	/* select the distance function */
	switch (tsp->edge_weight_type) {
	case EUC_2D:
		distance_func = euc_2d_distance_func;
		break;

	case GEOM:
		distance_func = geom_distance_func;
		break;

	default:
		return;
	}

	s = 0;
	for (j = 0; j < dimension; j ++) {
		for (k = j + 1; k < dimension; k ++) {
			distance_map[s] = distance_func \
				(node_coords[j],
				 node_coords[k]);
			s++;
		}
	}

	tsp->distance_map = distance_map;
}


/* ================================== */
/* IO Functions */

//struct tsplib_tsp_struct *
//tsplib_read_tsp
//	(FILE *file);

struct tsplib_tsp_struct *
tsplib_read_striped_tsp
	(FILE *file)
{
	int ret;
	struct tsplib_tsp_struct *tsp;
	unsigned int j, n, dimension;
	float x, y;
	char name_buf[32], type_buf[32];
	tsplib_edge_weight_type edge_weight_type;

	tsp = NULL;

	ret = fscanf(file, "NAME : %s\n", name_buf);
	if (ret != 1) {
		goto error;
	}

	ret = fscanf(file, "DIMENSION : %u\n", &dimension);
	if (ret != 1) {
		goto error;
	}

	ret = fscanf(file, "EDGE_WEIGHT_TYPE : %s\n", type_buf);
	if (ret != 1) {
		goto error;
	}

	edge_weight_type = tsplib_str_to_edge_weight_type \
		(type_buf,
		 strlen(type_buf));

	tsp = tsplib_tsp_new \
		(name_buf,
		 strlen(name_buf),
		 dimension,
		 edge_weight_type);
	if (tsp == NULL) {
		goto error;
	}

	ret = fscanf(file, "NODE_COORD_SECTION\n");
	if (ret != 0) {
		goto error;
	}

	for (j = 1; j <= dimension; j++) {
		ret = fscanf(file, "%u %f %f\n", &n, &x, &y);
		if ((ret != 3) | (n != j)) {
			goto error;
		}

		tsp->node_coords[j].x = x;
		tsp->node_coords[j].y = y;
	}

	tsplib_tsp_construct_distance_map(tsp);

	return tsp;

error:
	if (tsp) {
		tsplib_tsp_free(tsp);
	}
	return NULL;
}



using namespace std;

int iChosenSolution = 0;
int iMaxNumberOfIteretion = 0;
bool DEBUG = false;

int main(int argc, char **argv) {
	char *caSaveFileName = NULL;
	char *caLoadTableFileName = NULL;
	char *caSizeOfTable = NULL;
	bool bGenerate = false;

	FILE *pFile;
	pFile = fopen ("myfile.txt" , "r");
	struct tsplib_tsp_struct *x = tsplib_read_striped_tsp(pFile);


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

		c = getopt_long(argc, argv, "gl:s:i:tero:dw", long_options, &option_index);
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
				cout << "\t-s [integer]\t\t\tThe size of generated data." << endl;
				cout << "\t-l [filename]\t\t\tLoad generated date." << endl;
				cout << "\t-o [filename]\t\t\tOutput date." << endl;
				cout << "\t-r \t\t\tUse random algorithm." << endl;
				cout << "\t-t \t\t\tUse steepest algorithm." << endl;
				cout << "\t-e \t\t\tUse greedy algorithm." << endl;
				cout << "\t-w \t\t\tUse own algorithm." << endl;
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
		case 'e':
			iChosenSolution = iChosenSolution | GREEDY;
			break;
		case 'r':
			iChosenSolution = iChosenSolution | RANDOM;
			break;
		case 't':
			iChosenSolution = iChosenSolution | STEEPEST;
			break;
		case 'w':
			iChosenSolution = iChosenSolution | OWNSOLUTION;
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
		gen = new Generate(string(caLoadTableFileName));
	} else {
		cerr << "You have to load or generate table!" << endl;
		exit(1);
	}

	vector<int> *vec = new vector<int> ();

	for (int i = 0; i < gen->getNumberOfCities(); i++) {
		vec->push_back(i);
	}

//	cout << gen->calculateWholeDistance(vec) << endl;

	srand(time(NULL));

	Calculation *calc;

	//cout << "Calculating" << endl;
	if ((iChosenSolution & RANDOM) == RANDOM) {
		calc = new RandomCalculation();
		vec = (iMaxNumberOfIteretion) ? calc->solve(gen, iMaxNumberOfIteretion, caSaveFileName) : calc->solve(gen, caSaveFileName);
		//cout << "Random best solution" << endl;
		//cout << gen->calculateWholeDistance(vec) << endl;
		if (DEBUG)
			gen->DEBUG_printTrace(vec);
		delete calc;
	}
	if ((iChosenSolution & STEEPEST) == STEEPEST) {
		calc = new Steepest();
		vec = (iMaxNumberOfIteretion) ? calc->solve(gen, iMaxNumberOfIteretion, caSaveFileName) : calc->solve(gen, caSaveFileName);
//		cout << "Steepest best solution" << endl;
//		cout << gen->calculateWholeDistance(vec) << endl;
		if (DEBUG)
			gen->DEBUG_printTrace(vec);
		delete calc;
	}
	if ((iChosenSolution & GREEDY) == GREEDY) {
		calc = new Greedy();
		vec = (iMaxNumberOfIteretion) ? calc->solve(gen, iMaxNumberOfIteretion, caSaveFileName) : calc->solve(gen, caSaveFileName);
//		cout << "Greedy best solution" << endl;
//		cout << gen->calculateWholeDistance(vec) << endl;
		if (DEBUG)
			gen->DEBUG_printTrace(vec);
		delete calc;
	}
	if ((iChosenSolution & OWNSOLUTION) == OWNSOLUTION) {
		calc = new Own();
		vec = (iMaxNumberOfIteretion) ? calc->solve(gen, iMaxNumberOfIteretion, caSaveFileName) : calc->solve(gen, caSaveFileName);
//		cout << "Own best solution" << endl;
//		cout << gen->calculateWholeDistance(vec) << endl;
		if (DEBUG)
			gen->DEBUG_printTrace(vec);
		delete calc;
	}

	delete gen;

	return 0;
}
