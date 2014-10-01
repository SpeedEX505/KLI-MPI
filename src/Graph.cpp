#include "Graph.h"



using namespace std;

int Graph::readNodesCnt(const char * fileName) {
	string line;
	ifstream fin;
	int nodesCnt=0;

	fin.open(fileName, ios_base::in);
	if (!fin.is_open()) {
		fin.clear();
		return 0;
	}
	if(std::getline(fin, line)){
		nodesCnt=atoi(line.c_str());
	}else{
		cerr<<"Cannot read file "<<fileName<<endl;	
	}
	fin.close();
	cout << "Nodes to be loaded: " << line << endl;
	return nodesCnt;
}

int** Graph::readNodesMatrix(const char * fileName) {
	string line;
	ifstream fin;
	int ** matrix =new int*[nodesCnt];
	for(int i=0;i<nodesCnt;i++){
		matrix[i] = new int[nodesCnt];
	}
	fin.open(fileName, ios_base::in);
	if (!fin.is_open()) {
		fin.clear();
		return 0;
	}
	int lineCnt=0;
	std::getline(fin,line);
	while(std::getline(fin,line)){
		for(int i=0;i<nodesCnt;i++){
			matrix[lineCnt][i]=line.at(i)-48;
		}
		lineCnt++;		
	}
	fin.close();
	return matrix;
}

Graph::Graph(const char * filename){
	nodesCnt = readNodesCnt(filename);
	nodesMatrix = readNodesMatrix(filename);
}

Graph::~Graph(){
	for(int i=0; i < nodesCnt; i++) {
		delete nodesMatrix[i];	
	}
	delete nodesMatrix;
}

void Graph::print(){
	for(int i=0;i<nodesCnt;i++){
		for(int j=0;j<nodesCnt;j++){
			cout<<nodesMatrix[i][j]<<" ";
		}
		cout<<endl;
	}
}


