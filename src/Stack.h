#ifndef Stack_H
#define Stack_H
#include <cstdio>

/** Klasicky zasobnik k ukladani cisla uzlu
 */
class Stack{
private:
	int * array;
public:
	Stack();
	Stack(int * serializedStack);
	~Stack();
	bool equals(Stack * stack);
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
