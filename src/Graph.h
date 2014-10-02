#ifndef Graph_H
#define Graph_H
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <cstdlib>

class Graph{
	unsigned long nodesCnt;
	int ** nodesMatrix;
	int rowMatrix;
	int colMatrix;
	
	int readNodesCnt(const char * file); 		// reads number of nodes
	int ** readNodesMatrix(const char * file);	// reads nodes into matrix
public:
	Graph(const char * filename);
	~Graph();
	void print();
};

#endif
