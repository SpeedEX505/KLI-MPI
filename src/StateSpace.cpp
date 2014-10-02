#include "StateSpace.h"

#include "Stack.h"

StateSpace::StateSpace(int size){
	Stack stack;
	stack.push(1);
	stack.printStack();
	while(!stack.isEmpty()){
		if(stack.getTop()<size){
			stack.push(stack.getTop()+1);
		}else{
			stack.pull();
		}
		stack.printStack();
	}


}	
