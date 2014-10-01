#include "Graph.h"

Graph::Graph(){
	nodesCnt=0;
	nodes=0;
}

Graph::~Graph(){
	for(int i=0;i<nodesCnt;i++){
		delete nodes[i];	
	}
	delete nodes;
}

void Graph::parseFile(const char * filename){
	
}

void Graph::print(){
	for(int i=0;i<nodesCnt;i++){
		for(int j=0;j<nodesCnt;j++){
			//nodes->printNode());
		}
		printf("\n");
	}
}


