#ifndef Stack_H
#define Stack_H
#include <cstdio>

class StackNode{
public:
	int value;
	StackNode * next;

	StackNode(int value, StackNode * next){
		this->value = value;
		this->next = next;	// eq. null
	}
};

/** Klasicky zasobnik k ukladani cisla uzlu
 */
class Stack{
private:
	unsigned int stackSize;
	StackNode * node;
public:
	Stack();
	Stack(int * serializedStack);
	~Stack();
	void push(int value);
	int pull();
	int getTop();
	bool isEmpty();
	void printStack();
	int getSize();
	int * getArray();
	int * serialize();
};

#endif
