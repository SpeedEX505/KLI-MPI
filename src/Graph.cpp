#include "Graph.h"

Graph::Graph(long nodesCnt){
	this->nodesCnt=nodesCnt;
	matrix = new char*[nodesCnt];
	for(int i=0;i<nodesCnt;i++){
		matrix[i]=new char[nodesCnt];	
	}
}

Graph::~Graph(){
	for(int i=0;i<nodesCnt;i++){
		delete [] matrix[i];	
	}
	delete matrix;
}

void Graph::print(){
	for(int i=0;i<nodesCnt;i++){
		for(int j=0;j<nodesCnt;j++){
			printf("%d ",matrix[i][j]);
		}
		printf("\n");
	}
}
