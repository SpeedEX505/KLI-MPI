#ifndef Stack_H
#define Stack_H
#include <cstdio>

class StackNode{
public:
	int value;
	StackNode * next;
	StackNode(int value){
		this->value=value;
		this->next=0;
	}
};

class Stack{
	unsigned int stackSize;
	StackNode * node;
public:
	Stack();
	void push(int value);
	int pull();
};

#endif
