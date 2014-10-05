#ifndef ProblemSolver_H
#define ProblemSolver_H
#include <cstdio>
#include <iostream>
#include <cstdlib>

#include "Graph.h"
#include "Stack.h"

class ProblemSolver{
	Graph* graph;
public:
	ProblemSolver(Graph* graph){
		this->graph=graph;
	}
	void SolveProblem();
	bool isClique(Stack stack);
};

#endif
