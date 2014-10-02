#include "ProblemSolver.h"
#include "Stack.h"
void ProblemSolver::SolveProblem(){
	std::cout<<"Solving problem..."<<std::endl;

	Stack stack;

	stack.push(1);
	stack.push(2);
	stack.push(3);

	printf("top: %d\n",stack.getTop());	
	printf("pulled: %d\n",stack.pull());
	printf("pulled: %d\n",stack.pull());
	printf("pulled: %d\n",stack.pull());
	printf("pulled: %d\n",stack.pull());
	std::cout<<"TODO"<<std::endl;
}


