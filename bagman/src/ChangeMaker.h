/*
 * ChangeMaker.h
 *
 *  Created on: Nov 5, 2010
 *      Author: piekar294
 */

#ifndef CHANGEMAKER_H_
#define CHANGEMAKER_H_

#include "Generate.h"

class ChangeMaker {
public:
	ChangeMaker(Generate *topology);
	void transform_2opt(vector<int> *tour, int pos1, int pos2);
	void transform_kopt(vector<int> *tour, int poses[], int k);
	void transform_kopt(vector<int> *tour, vector<int> *poses);

	virtual ~ChangeMaker();

private:
	Generate *_topology;
};

#endif /* CHANGEMAKER_H_ */
