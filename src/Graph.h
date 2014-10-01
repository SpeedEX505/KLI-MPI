#ifndef Graph_H
#define Graph_H
#include <cstdio>
#include <iostream>
#include <cstdlib>

class Graph{
	unsigned long nodesCnt;
	int ** nodesMatrix;
	int readNodesCnt(const char * file); 		// reads number of nodes
	int ** readNodesMatrix(const char * file);	// reads nodes into matrix
public:
	Graph(const char * filename);
	~Graph();
	void print();
};

#endif
