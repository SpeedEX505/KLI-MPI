#ifndef Graph_H
#define Graph_H
#include <cstdio>

class Graph{
	long nodesCnt;
	char ** matrix;
public:
	Graph(long nodesCnt);
	~Graph();
	void print();
};

#endif
