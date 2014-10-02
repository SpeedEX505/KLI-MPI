#include "Stack.h"

Stack::Stack(){
	node = 0;
	stackSize = 0;
}

void Stack::push(int value){
	StackNode * newNode = new StackNode(value);
	if (this->node == 0){
		this->node = node;
	} else {
		newNode->next = this->node;
		this->node = newNode;
	}
	this->stackSize++;
}

int Stack::pull(){
	if (this->stackSize == 0){
		printf("Stack is empty");
		return -1;
	}

	StackNode * toDelete = this->node;
	int value = this->node->value;
	if (this->node->next == 0){
		this->node = 0;
	} else {
		this->node = this->node->next;	
	}
	this->stackSize--;

	delete toDelete;
	return value;
}
