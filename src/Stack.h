#ifndef Stack_H
#define Stack_H
#include <cstdio>

class StackNode{
public:
	int value;
	StackNode * next;

	StackNode(int value){
		this->value = value;
		this->next = 0;	// eq. null
	}
};

class Stack{
private:
	unsigned int stackSize;
	StackNode * node;
public:
	Stack();
	void push(int value);
	int pull();
	int getTop();
	bool isEmpty();
	void printStack();
	int getSize();
	int * getArray();
};

#endif
