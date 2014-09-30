#include <iostream>

#include "Graph.h"

//TODO: Parsing graph from file
Graph* parseGraph(const char *file){
	return new Graph(10);
} 

int main(int argc, char ** argv) {
	Graph* g = parseGraph("graph.txt");
	g->print();
	return 0;
}
