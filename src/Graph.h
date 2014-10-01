#ifndef Graph_H
#define Graph_H
#include <cstdio>
#include <iostream>

class Graph{
	unsigned long nodesCnt;
	int ** nodesMatrix;
	// precte prvni radek ve filu -> pocet uzlu
	int readNodesFile(const char * file);
public:
	Graph();
	Graph(unsigned long nodesCnt);
	~Graph();
	// parse value in file to matrix
	void parseFile(const char * filename);
	void print();
};

#endif
