/*
 * ChangeMaker.cpp
 *
 *  Created on: Nov 5, 2010
 *      Author: piekar294
 */

#include "ChangeMaker.h"

ChangeMaker::ChangeMaker(Generate *topology): _topology(topology) {
}

ChangeMaker::~ChangeMaker() {

	//TODO: dogadac sie czy potrzebne
	/*if (_topology != null) {
		delete _topology;
	}*/
}

void ChangeMaker::transform_2opt(vector<int> *tour, int pos1, int pos2) {
	//just swap 2 elements
	int tmp = tour->at(pos1);
	(*tour)[pos1] = (*tour)[pos2];
	(*tour)[pos2] = tmp;

	return;
}

void ChangeMaker::transform_kopt(vector<int> *tour, int poses[], int k) {
	//save first element
	int tmp = tour->at(poses[0]);

	//swap next elements until the last one
	for (int i = 0; i < k-1; i++)
	{
		(*tour)[poses[i]] = (*tour)[poses[(i+1)]];
	}

	//swap last element with the first one
	(*tour)[poses[k-1]] = tmp;

	return;
}

void ChangeMaker::transform_kopt(vector<int> *tour, vector<int> *poses) {
	//save first element
	int tmp = tour->at(poses->at(0));

	//swap next elements until the last one
	for (unsigned int i = 0; i < poses->size()-1; i++)
	{
		(*tour)[poses->at(i)] = (*tour)[poses->at(i+1)];
	}

	//swap last element with the first one
	(*tour)[poses->at(poses->size() -1)] = tmp;

	return;
}
