/*
 * TSPTabuSearchSolver.cpp
 *
 *  Created on: 2010-11-26
 *      Author: kolczak
 */

#include "TSPTabuSearchSolver.h"

TSPTabuSearchSolver::TSPTabuSearchSolver(Instance *inst, string output) : TSPSolver(output) {
	// TODO Auto-generated constructor stub
		TSPSolver::_instance = inst;
		saver = new TSPDataSaver(output.c_str(), inst);
}

TSPTabuSearchSolver::TSPTabuSearchSolver(u_int32_t size, string output) : TSPSolver(output) {
	_instance = Instance::generateRandomInstance(size);
		saver = new TSPDataSaver(output.c_str(), _instance);
}

TSPTabuSearchSolver::~TSPTabuSearchSolver() {
	// TODO Auto-generated destructor stub
}
