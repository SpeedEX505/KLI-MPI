#include "ProblemSolver.h"
#include "Graph.h"
#include "Stack.h"
using namespace std;

void ProblemSolver::SolveProblem(){
	Stack stack;
	int lastNode = graph->size()-1;
	stack.push(0);
	stack.printStack();
	bool returning=false;
	while(true){
		if(stack.isEmpty()){
			break;
		}
		if(!returning&&stack.getTop()<lastNode){
			stack.push(stack.getTop()+1);
			isClique(stack);
			continue;
		}
		if(returning&&stack.getTop()<lastNode){
			int value=stack.pull()+1;
			stack.push(value);
			returning=false;
			isClique(stack);
			continue;
		}
		if(stack.getTop()==lastNode){
			stack.pull();
			returning=true;
			continue;
		}
	}
}

bool ProblemSolver::isClique(Stack stack){
	int arrSize = stack.getSize();
	int *values = stack.getArray();
	for(int i=0;i<arrSize;i++){
		for(int j=0;j<arrSize;j++){
			if(i==j) continue;
			if(graph->isConnected(values[i],values[j])==false){
				return false;
			}
		}
	}
	cout<<"Clique founded: size("<<arrSize<<")"<<endl;
	stack.printStack();
	return true;
}


