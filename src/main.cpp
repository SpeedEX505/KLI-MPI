#include <iostream>
#include "mpi.h"

#include "Graph.h"
#include "ProblemSolver.h"
#include "MPIHolder.h"

int main(int argc, char ** argv) {
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &(MPIHolder::getInstance().myRank)); 	//vyplneni singletonu - idProcesu
	MPI_Comm_size(MPI_COMM_WORLD, &(MPIHolder::getInstance().cpuCounter));  //vyplneni singletonu - pocetProcesu
	Graph * g = new Graph("graph.txt");
	MPI_Barrier(MPI_COMM_WORLD);		// vsechny procesy jiz nacetly graf
	ProblemSolver ps(g);
	if(MPIHolder::getInstance().myRank==0){	// master proces					
		ps.sendWorkAtStart();		// poslat praci slave procesům	
	}else{					// slave procesy
		ps.listenAtStart();		// naslouchat na praci od mastera
	}
	MPI_Barrier(MPI_COMM_WORLD); // prace je rozdistribuvovana
	// vsichni procesy maji praci nyni se muzou zacit chovat rovnocene a pocitat do zblazneni	
	ps.startComputing();
	
	ps.printResults(); // sebrat vysledky a vytisknout
	delete g;
	//std::cout<<"Ukoncuji se "<<MPIHolder::getInstance().myRank<<std::endl;
	MPI_Finalize();
	return 0;
}
