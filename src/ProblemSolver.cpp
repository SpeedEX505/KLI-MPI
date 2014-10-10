#include "ProblemSolver.h"
#include "Graph.h"
#include "Stack.h"
using namespace std;

void MaxClique::destroyArray(){
	if (this->arrayNodes != NULL)	
		delete [] arrayNodes;
}

void MaxClique::cpyArrayNodes(int * array, int size){
	this->size = size;
	this->arrayNodes = new int[size];
	for (int i = 0; i < size; i++) 
		this->arrayNodes[i] = array[i];
}

MaxClique::MaxClique(){
	this->size = 0;
	this->arrayNodes = NULL;
}

MaxClique::~MaxClique(){
	destroyArray();
}

int MaxClique::sizeArray(){
	return this->size;
}

bool MaxClique::isBiggerThan(int size){
	return (this->size > size);
}

bool MaxClique::isSmallerThan(int size){
	return (this->size < size);
}

void MaxClique::addArrayNodes(int * array, int size){
	destroyArray();
	cpyArrayNodes(array, size);
}

void MaxClique::printArrayNodes(){
	cout << "Nodes: ";
	for (int i = 0; i < this->size; i++)
		cout << this->arrayNodes[i] << " ";
}
// ------------------------------------------------------------------------------------------------

ProblemSolver::ProblemSolver(Graph* graph){
	this->graph = graph;
}

void ProblemSolver::SolveProblem(){
	Stack * stack = new Stack();
	int lastNode = graph->size()-1;	
	stack->push(0);
	int lastDeleted=-1;

	while(true){
		if(stack->isEmpty())	break;
		if(stack->getTop() < lastNode){
			int toPush=lastDeleted;			
			if(toPush==-1){
				toPush=stack->getTop()+1;
			}else{
				if(++toPush>lastNode){
					lastDeleted=stack->pull();
					continue;
				}
			}
			stack->push(toPush);
			lastDeleted=-1;
			if(isClique(stack) == false){
				lastDeleted=stack->pull();
			}
			continue;
		}
		if(stack->getTop() == lastNode){
			lastDeleted=stack->pull();
			continue;
		}
	}

	delete stack;
	this->printMaxClique();
	cout << endl;
}

bool ProblemSolver::isClique(Stack * stack){
	int arrSize = stack->getSize();
	int *values = stack->getArray();
	
	for(int i = 0; i < arrSize; i++){
		for(int j = 0; j < arrSize; j++){
			if(i == j) continue;
			if(graph->isConnected(values[i], values[j]) == false){
				delete []values;
				return false;
			}
		}
	}
	if (maxClique.isSmallerThan(arrSize)){
		maxClique.addArrayNodes(values, arrSize);
		cout << "Bigger clique founded, size(" << arrSize << ")" << endl;
		stack->printStack();
	}

	delete [] values;
	return true;
}

void ProblemSolver::printMaxClique(){
	cout << "Max clique size is/are: " << this->maxClique.sizeArray() << endl;
	this->maxClique.printArrayNodes();
}

