#ifndef ProblemSolver_H
#define ProblemSolver_H
#include <cstdio>
#include <iostream>
#include <cstdlib>

#include "Graph.h"
#include "Stack.h"

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
	bool biggerThan(int size);
	void addArrayNodes(int * array, int size);
	void printArrayNodes();
};

/** Testovaci trida, ktera vygeneruje stavovy prostor + hleda kliky 
 * v podgrafu
 * 
 */
class ProblemSolver{
	Graph* graph;
	MaxClique maxClique;
public:
	ProblemSolver(Graph * graph);
	void SolveProblem();
	bool isClique(Stack stack);
	void printMaxClique();
};

#endif
