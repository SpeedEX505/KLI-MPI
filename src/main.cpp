#include <iostream>
#include "mpi.h"

#include "Graph.h"
#include "ProblemSolver.h"


int main(int argc, char ** argv) {
	MPI_Init(&argc, &argv);
	Graph * g = new Graph("graph.txt");
	g->print();

	ProblemSolver ps(g);
	ps.SolveProblem();
	
	delete g;
	MPI_Finalize();
	return 0;
}
