#include <iostream>
#include "mpi.h"

#include "Graph.h"
#include "ProblemSolver.h"
#include "MPIHolder.h"

int main(int argc, char ** argv) {
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &(MPIHolder::getInstance().myRank)); //find out process rank
	MPI_Comm_size(MPI_COMM_WORLD, &(MPIHolder::getInstance().cpuCounter)); //find out number of processors
	if(MPIHolder::getInstance().myRank==0){
	Graph * g = new Graph("graph.txt");
	g->print();
	
	
	ProblemSolver ps(g);
	ps.SolveProblem();
	
	
	delete g;
	}else{
	    std::cout<<"nejsem master procesor, nedelam nic."<<std::endl;
	}
	MPI_Finalize();
	return 0;
}
