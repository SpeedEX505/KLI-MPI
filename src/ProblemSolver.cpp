#include "ProblemSolver.h"
#include "Graph.h"
#include "Stack.h"

#include "MPIHolder.h"
using namespace std;

void MaxClique::destroyArray(){
	if (this->arrayNodes != NULL)	
		delete [] arrayNodes;
}

void MaxClique::cpyArrayNodes(int * array, int size){
	this->size = size;
	this->arrayNodes = new int[size];
	for (int i = 0; i < size; i++) 
		this->arrayNodes[i] = array[i];
}

MaxClique::MaxClique(){
	this->size = 0;
	this->arrayNodes = NULL;
}

MaxClique::~MaxClique(){
	destroyArray();
}

int MaxClique::getSize(){
	return this->size;
}

bool MaxClique::isBiggerThan(int size){
	return (this->size > size);
}

bool MaxClique::isSmallerThan(int size){
	return (this->size < size);
}

void MaxClique::addArrayNodes(int * array, int size){
	destroyArray();
	cpyArrayNodes(array, size);
}

void MaxClique::printArrayNodes(){
	cout << "Nodes: ";
	for (int i = 0; i < this->size; i++)
		cout << this->arrayNodes[i] << " ";
}
// ------------------------------------------------------------------------------------------------

ProblemSolver::ProblemSolver(Graph* graph){
	this->graph = graph;
	state = STATE_IDLE;
	tokenColor=TOKEN_WHITE;
	lastAsked=MPIHolder::getInstance().myRank;
	token=0;
	terminate=false;
	endSize=0;
	workRequestSent=false;
}

void ProblemSolver::WorkDone(){
	state=STATE_IDLE;
	if(token!=0){
		int dest=(MPIHolder::getInstance().myRank+1)%(MPIHolder::getInstance().cpuCounter);
		if(token[0]==TOKEN_WHITE&&tokenColor==TOKEN_BLACK){
			token[0]=TOKEN_BLACK;
		}
		if(token[1]<maxClique.getSize()){
			token[1]=maxClique.getSize();
			token[2]=MPIHolder::getInstance().myRank;
		}
		MPI_Send(token, MPIHolder::getInstance().stackMaxSize, MPI_INT,dest, FLAG_TOKEN, MPI_COMM_WORLD);		
		tokenColor=TOKEN_WHITE;
		token=0;
	}
}

//TODO dodělat --> nekde se to tu cykli
void ProblemSolver::solveSubtree(){
	int lastDeleted=-1;
	int lastNode = graph->size()-1;	
	int citac=0;
	
	do{	
		if(citac%100==0&&lastDeleted==-1){
			return;
		}
		if(stack->getTop() < lastNode){
			int toPush=lastDeleted;			
			if(toPush==-1){
				toPush=stack->getTop()+1;
			}else{
				if(++toPush>lastNode){
					lastDeleted=stack->pull();
					continue;
				}
			}
			stack->push(toPush);
			lastDeleted=-1;
			citac++;
			if(isClique(stack) == false){
				lastDeleted=stack->pull();
			}
			continue;
		}
		if(stack->getTop() == lastNode){
			lastDeleted=stack->pull();
			continue;
		}
	}while(stack->getSize()<=endSize);
	WorkDone();
}



//Kontrola na pocet uzlu a ochrana proti (vice uzlu nez prace)
void ProblemSolver::sendWorkAtStart(){
	cout<<"CPU"<<MPIHolder::getInstance().myRank<<": Sending work at start..."<<endl;
	int cpuCnt=MPIHolder::getInstance().cpuCounter;
	int destinationCPU=1;	
	stack = new Stack();
	int lastNode = graph->size()-1;
	int lastDeleted=-1;
	
	while(true){
		stack->push(lastDeleted+1);
		if(lastDeleted+1==lastNode){
			break;
		}
		if(destinationCPU<cpuCnt){
			int * array=stack->serialize();
			MPI_Send (array, MPIHolder::getInstance().stackMaxSize, MPI_INT, destinationCPU, FLAG_JOB_SEND, MPI_COMM_WORLD);
			lastDeleted=stack->pull();
			destinationCPU++;
		}else{
			break;		
		}
	}
	int * pomArray = new int[MPIHolder::getInstance().stackMaxSize];
	pomArray[0]=0;
	while(destinationCPU<cpuCnt){
		MPI_Send(pomArray,MPIHolder::getInstance().stackMaxSize,MPI_INT,destinationCPU,FLAG_JOB_SEND,MPI_COMM_WORLD);
		destinationCPU++;
	}
	delete [] pomArray;
	endSize=0;
	state=STATE_ACTIVE;
}


void ProblemSolver::listenAtStart(){
	cout<<"CPU"<<MPIHolder::getInstance().myRank<<": Listening at start..."<<endl;
	int array[MPIHolder::getInstance().stackMaxSize];
	MPI_Status status;
	MPI_Recv(&array, MPIHolder::getInstance().stackMaxSize, MPI_INT, MPI_ANY_SOURCE, FLAG_JOB_SEND, MPI_COMM_WORLD, &status);
	stack = new Stack(array);
	endSize=stack->getSize();
	if(endSize>0)state=STATE_ACTIVE;
}

void ProblemSolver::startComputing(){
	while(!terminate){
		switch(state){
			case STATE_ACTIVE:
				solveSubtree();
				checkMessages();
				break;
			case STATE_IDLE:
				if(!workRequestSent) getNewWork();
				checkMessages();
				break;
		}	
	}
}

void ProblemSolver::Token(int * buffer){
	if(state==STATE_ACTIVE){
		token=buffer; // store token
	}else{
		//aktualizovat a odeslat token
	}
}
void ProblemSolver::JobRequest(int * buffer,int source){
	Stack * stackToSend = divideStack();	
	if(stackToSend==0){
		int * array=new int[1];
		MPI_Send(array, 1, MPI_INT, source, FLAG_JOB_SEND, MPI_COMM_WORLD);
	}else{
		MPI_Send( stackToSend->serialize(),MPIHolder::getInstance().stackMaxSize, MPI_INT,source,FLAG_JOB_SEND,MPI_COMM_WORLD);
		if(source<MPIHolder::getInstance().myRank){
			tokenColor=TOKEN_BLACK;
		}
	}
}

void ProblemSolver::JobReceived(int * buffer){
	state=STATE_ACTIVE;
	tokenColor=TOKEN_WHITE;
	stack = new Stack(buffer);
	endSize = stack->getSize();
	workRequestSent=false;
}
void ProblemSolver::NoJobReceived(){
	workRequestSent=false;
}


//TODO 
// Zjisti zda se vyplati davat praci. Pokud ano rozdělí stack a vratí ho. Presune stack na dalsi uzel. [musi ho zkotrolovat protoze solve subtree predpoklada zkontrolovany stav]
// pokud se to nevyplati vrati null (0)
Stack * ProblemSolver::divideStack(){
	return 0;
}

Stack * ProblemSolver::getNewWork(){
	int askerId = askerID();
    int buffer[MPIHolder::getInstance().stackMaxSize];
	MPI_Send(new int[MPIHolder::getInstance().stackMaxSize],MPIHolder::getInstance().stackMaxSize, MPI_INT,askerID(),FLAG_JOB_REQUEST,MPI_COMM_WORLD);
}

// TODO bere jen jednu zpravu
void ProblemSolver::checkMessages(){
	int flag;
	MPI_Status status;
	while(true){
		MPI_Iprobe(MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &flag, &status);
		if(flag==0) return;

		int buffer[MPIHolder::getInstance().stackMaxSize];
		MPI_Recv(&buffer, MPIHolder::getInstance().stackMaxSize, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
		switch(flag){
			case FLAG_TOKEN:	//Přišel token
				Token(buffer);
				break;
			case FLAG_JOB_REQUEST: 	//nekdo zada o praci
				JobRequest(buffer,0); // TODO !!!!!! Jak dostat ze status source prichozí zpravy??? nahradit za 0 jako druhy parametr
				break;
			case FLAG_JOB_SEND: 	// prisla prace 
				JobReceived(buffer);
				break;
			case FLAG_JOB_NONE: 	// neni prace
				NoJobReceived();
				break;
		}
	}
}

bool ProblemSolver::isClique(Stack * stack){
	int arrSize = stack->getSize();
	int *values = stack->getArray();
	
	for(int i = 0; i < arrSize; i++){
		for(int j = 0; j < arrSize; j++){
			if(i == j) continue;
			if(graph->isConnected(values[i], values[j]) == false){
				delete []values;
				return false;
			}
		}
	}
	if (maxClique.isSmallerThan(arrSize)){
		maxClique.addArrayNodes(values, arrSize);
	}

	delete [] values;
	return true;
}

void ProblemSolver::printMaxClique(){
	cout << "Max clique size is/are: " << this->maxClique.getSize() << endl;
	this->maxClique.printArrayNodes();
}

int ProblemSolver::askerID(){
	lastAsked = (lastAsked+1) % (MPIHolder::getInstance().cpuCounter);
	if(lastAsked==MPIHolder::getInstance().myRank){
		lastAsked = (lastAsked+1) % (MPIHolder::getInstance().cpuCounter);
	}
	return lastAsked;	
}

