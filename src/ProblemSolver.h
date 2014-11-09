#ifndef ProblemSolver_H
#define ProblemSolver_H
#include <cstdio>
#include <iostream>
#include <cstdlib>

#include "Graph.h"
#include "Stack.h"
#include "MPIHolder.h"
#include "mpi.h"

/** Uchovani nejvetsi kliky
 */
class MaxClique{
private:
	int size;
	int * arrayNodes;
	void destroyArray();
	void cpyArrayNodes(int * array, int size);
public:
	MaxClique();
	~MaxClique();
	int sizeArray();
	bool isBiggerThan(int size);
	bool isSmallerThan(int size);
	void addArrayNodes(int * array, int size);
	void printArrayNodes();
};

/** Testovaci trida, ktera vygeneruje stavovy prostor + hleda kliky 
 * v podgrafu
 * 
 */
class ProblemSolver{
	Graph* graph;
	Stack * stack;
	MaxClique maxClique;
	Stack * getNewWork();
	bool checkWorkAdepts();
	bool isClique(Stack * stack);
	void solveSubtree(Stack * stack);
public:
	ProblemSolver(Graph * graph);
	void SolveProblem();
	void sendWorkAtStart();
	void listenAtStart();
	void startComputing();
	void aduv();
	void printMaxClique();
};

#endif
