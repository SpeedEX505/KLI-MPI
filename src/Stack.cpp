#include "Stack.h"

Stack::Stack(){
	node=0;
	stackSize=0;
}

void Stack::push(int value){
	StackNode * node = new StackNode(value);
	if(this->node==0){
		this->node=node;
	}else{
		node->next=this->node;
		this->node=node;
	}
	this->stackSize+=1;
}

int Stack::pull(){
	if(this->stackSize==0){
		printf("Stack is empty");
		return -1;
	}
	StackNode * toDelete = this->node;
	int value = this->node->value;
	if(this->node->next==0){
		this->node=0;
	}else{
		this->node=this->node->next;	
	}
	this->stackSize-=1;
	delete toDelete;
	return value;
}
