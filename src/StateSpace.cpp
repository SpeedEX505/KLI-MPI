#include "StateSpace.h"

#include "Stack.h"

StateSpace::StateSpace(int size){
	Stack stack;
	stack.push(1);
	stack.printStack();
	while(true){
		if(stack.getTop()<size){
			stack.push(stack.getTop()+1);
		}else{
			stack.pull();
			int value=stack.pull();
			if(value==-1){
				break;
			}
			stack.push(value+1);
		}
		stack.printStack();
	}


}	
