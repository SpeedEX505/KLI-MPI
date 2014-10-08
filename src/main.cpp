#include <iostream>

#include "Graph.h"
#include "ProblemSolver.h"


int main(int argc, char ** argv) {
	Graph * g = new Graph("graph.txt");
	g->print();

	ProblemSolver ps(g);
	ps.SolveProblem();
	
	//delete g;
	return 0;
}
