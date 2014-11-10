#ifndef ProblemSolver_H
#define ProblemSolver_H
#include <cstdio>
#include <iostream>
#include <cstdlib>

#include "Graph.h"
#include "Stack.h"
#include "MPIHolder.h"
#include "mpi.h"

#define STATE_ACTIVE 500
#define STATE_IDLE 501

#define TOKEN_WHITE 1000
#define TOKEN_BLACK 1001

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
	int getSize();
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
	Stack* stack;
	MaxClique maxClique;

	int state; 				// stav procesoru
	int tokenColor;			// barva
	bool terminate;			// skoncil aduv?
	bool workRequestSent; 	// proti deadlocku 
	int * token;			// token array nebo NULL pokud nema u sebe token
	int lastAsked;			// naposledy dotazovaný procesor (getJob)
	int endSize;			// ukoncovaci podminka solveSubtree

	Stack* divideStack(); 	// rozdělí stack a vratí ho. Pokud se nevyplatí vrati null
	void WorkDone(); 		//Prace dodelana, nastavi promenne popr. pošle token dal
	Stack* getNewWork(); 	// zada o novou praci
	void checkMessages();	// Přijme zprávy a obslouží je

	void Token(int * buffer);
	void JobRequest(int * buffer, int source);
	void JobReceived(int * buffer);
	void NoJobReceived();
		

	bool isClique(Stack * stack);
	void solveSubtree(); 	// řeší dany podstrom na zaklade promenne stack
	int askerID();			//získa id procesu, ktereho se ma zeptat na praci;
public:
	ProblemSolver(Graph * graph);	
	void sendWorkAtStart();	// distribuje praci
	void listenAtStart();	// nasloucha na praci
	void startComputing();	// zahajeni vypoctu
	void printMaxClique();
};

#endif
