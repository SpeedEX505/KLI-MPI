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

bool MaxClique::biggerThan(int size){
	return (this->size > size);
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
	Stack stack;
	int lastNode = graph->size()-1;	
	stack.push(0);
	stack.printStack();
	bool returning = false;
	cout << endl;

	while(true){
		if(stack.isEmpty())	break;
		if(!returning && stack.getTop() < lastNode){
			stack.push(stack.getTop() + 1);
			isClique(stack);
			continue;
		}
		if(returning && stack.getTop() < lastNode){
			int value=stack.pull()+1;
			stack.push(value);
			returning = false;
			isClique(stack);
			continue;
		}
		if(stack.getTop() == lastNode){
			stack.pull();
			returning=true;
			continue;
		}
	}

	this->printMaxClique();
	cout << endl;
}

bool ProblemSolver::isClique(Stack stack){
	int arrSize = stack.getSize();
	int *values = stack.getArray();
	
	for(int i = 0; i < arrSize; i++){
		for(int j = 0; j < arrSize; j++){
			if(i == j) continue;
			if(graph->isConnected(values[i], values[j]) == false){
				return false;
			}
		}
	}
	if (!maxClique.biggerThan(arrSize))
		maxClique.addArrayNodes(values, arrSize);

	cout << "Clique founded, size(" << arrSize << ")" << endl;
	stack.printStack();

	delete [] values;
	return true;
}

void ProblemSolver::printMaxClique(){
	cout << "Max clique size is/are: " << this->maxClique.sizeArray() << endl;
	this->maxClique.printArrayNodes();
}

