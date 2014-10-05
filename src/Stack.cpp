#include "Stack.h"

#include <iostream>

Stack::Stack(){
	node = 0;
	stackSize = 0;
}

void Stack::push(int value){
	StackNode * newNode = new StackNode(value);
	if (this->node == 0){
		this->node = newNode;
	} else {
		newNode->next = this->node;
		this->node = newNode;
	}
	this->stackSize++;
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
	
	this->stackSize--;

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

