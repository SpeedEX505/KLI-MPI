#include "Graph.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>


using namespace std;

int Graph::readNodesFile(const char * fileName) {
	string line;
	ifstream fin;

	fin.open(fileName, ios_base::in);
	if (!fin.is_open()) {
		fin.clear();
		return 0;
	}

	line = getline(fin, line);
	cout << "Nacteny pocet uzlu: " << line << endl;
}

Graph::Graph(){
	nodesCnt = readNodesFile("graph.txt");
	nodesMatrix = 0;

	// init matrix with null
	//for(int i = 0; i < )
}

Graph::~Graph(){
	for(int i=0; i < nodesCnt; i++) {
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


