#include "Graph.h"
#include "Stack.h"

using namespace std;

int Graph::readNodesCnt(const char * fileName) {
	string line;
	ifstream fin;
	int nodesCnt = 0;

	fin.open(fileName, ios_base::in);
	if (!fin.is_open()) {
		fin.clear();
		return 0;
	}
	if (std::getline(fin, line)){
		nodesCnt = atoi(line.c_str());
	} else {
		cerr << "Cannot read file " << fileName<<endl;	
	}

	fin.close();
	cout << "Nodes to be loaded: " << line << endl;
	return nodesCnt;
}

int** Graph::readNodesMatrix(const char * fileName) {
	int ** matrix = new int*[nodesCnt];
	for (int i = 0; i < nodesCnt; i++){
		matrix[i] = new int[nodesCnt];
	}

	// open file stream
	ifstream fin;
	fin.open(fileName, ios_base::in);
	if (!fin.is_open()) {
		fin.clear();
		return 0;
	}

	// load values
	string line;
	int lineCnt = 0;
	std::getline(fin, line);
	while (std::getline(fin, line)){
		for (int i = 0; i < this->nodesCnt; i++){
			matrix[lineCnt][i] = line.at(i) - 48; // char - possition to get number
		}
		lineCnt++;		
	}
	fin.close();
	return matrix;
}

//-------------------------------------------------------------------------------------------------
Graph::Graph(const char * filename){
	nodesCnt = readNodesCnt(filename);
	nodesMatrix = readNodesMatrix(filename);
}

Graph::~Graph(){
	for(int i = 0; i < nodesCnt; i++) {
		delete [] nodesMatrix[i];	
	}
	delete [] nodesMatrix;
}

int Graph::size() {
	return nodesCnt;
}

void Graph::print(){
	for (int i = 0; i < this->nodesCnt; i++){
		cout << "n" << i << ": ";
		for (int j = 0; j < this->nodesCnt; j++) {
			cout << nodesMatrix[i][j] << " ";
		}
		cout << endl;
	}
}

bool Graph::isConnected(int node1, int node2) {
	return (nodesMatrix[node1][node2] == 1);
}
