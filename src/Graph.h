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
	
	int readNodesCnt(const char * file); 		// reads number of nodes
	int ** readNodesMatrix(const char * file);	// reads nodes into matrix
public:
	Graph(const char * filename);
	Graph(int size);
	~Graph();
	// number of nodes
	int size();
	// matrix
	void print();

	// add edge between two nodes
	void addEdge(int node1, int node2);
	// are the node1 and node2 connected?
	bool isConnected(int node1, int node2);
};

#endif
