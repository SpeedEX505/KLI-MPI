#include "Stack.h"

#include <iostream>

Stack::Stack(){
	node = 0;
	stackSize = 0;
}

Stack::Stack(int * serializedStack){
	stackSize=serializedStack[0];
	node=0;
	for(int i=1;i<stackSize+1;i++){
		node = new StackNode(serializedStack[i],node);
	}
}

Stack::~Stack(){
	StackNode * p =node;
	StackNode * toDelete;	
	while(p!=0){
		toDelete = p;
		p = p->next;
		delete toDelete;
	}
}

int * Stack::serialize(){
	int * array = new int[stackSize+1]; 
	array[0]=stackSize;
	StackNode *p =node;
	for(int i=stackSize;i>0;i--){
		array[i]=p->value;
		p=p->next;
	}
	return array;
}

void Stack::push(int value){
	if (this->node == 0){
		this->node = new StackNode(value,0);
	} else {
		this->node = new StackNode(value,this->node);
	}
	(this->stackSize)++;
}

int Stack::pull(){
	if (this->stackSize == 0){
		std::cerr << "Stack is empty\n";
		return -1;
	}

	StackNode * toDelete = this->node;
	int value = this->node->value;
	if (this->node->next == 0)
		this->node = 0;
	else 
		this->node = this->node->next;	
	
	(this->stackSize)--;

	delete toDelete;
	return value;
}

int Stack::getTop(){
	if(this->node == 0){
		std::cerr << "Stack is empty\n";
		return -1;	
	}
	return this->node->value;
}

bool Stack::isEmpty(){
	return (this->stackSize == 0);
}

void Stack::printStack(){
	StackNode * p = this->node;
	std::cout<<"Stack: ";
	while(p!=0){
		std::cout<<p->value<<" ";
		p=p->next;
	}
	std::cout<<std::endl;	
}

int Stack::getSize(){
	return this->stackSize;
}

int * Stack::getArray(){
	int * arr = new int[this->stackSize];
	StackNode * p = this->node;
	for(int i = (stackSize - 1); i >= 0; i--){
		arr[i] = p->value;
		p = p->next;
	}
	return arr;
}

