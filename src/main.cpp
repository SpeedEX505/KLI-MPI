#include <iostream>

#include "Graph.h"
#include "Stack.h"

int main(int argc, char ** argv) {
	Graph * g = new Graph("graph.txt");
	g->print();


	return 0;
}
