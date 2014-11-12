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

int * MaxClique::serialize(){
	int * array = new int[MPIHolder::getInstance().stackMaxSize];
	array[0]=size;
	for(int i=1;i<=size;i++){
		array[i]=arrayNodes[i-1];
	}
	return array;
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
	p0TokenSent=false;
}

//dodelal svuj subtree
void ProblemSolver::WorkDone(){
	state=STATE_IDLE;		// je ze me IDLE
	if(token!=0){			// pokud drzim token obslouzi ho
		int dest=(MPIHolder::getInstance().myRank+1)%(MPIHolder::getInstance().cpuCounter);
		if(token[0]==TOKEN_WHITE&&tokenColor==TOKEN_BLACK){
			token[0]=TOKEN_BLACK;
		}
		if(token[1]<maxClique.getSize()){
			token[1]=maxClique.getSize();
			token[2]=MPIHolder::getInstance().myRank;
		}
		MPI_Send(token, MPIHolder::getInstance().stackMaxSize, MPI_INT,dest, FLAG_TOKEN, MPI_COMM_WORLD);		
		tokenColor=TOKEN_WHITE;		// odeslal jsem token obarvim se na bilo
		token=0;
	}
}


//expanduje stavy a resi je
void ProblemSolver::solveSubtree(){
	int lastDeleted=-1;
	int lastNode = graph->size()-1;	
	int citac=1;
	
	while(true){
		if((stack->getSize()<endSize) || (stack->getSize()==0)&&lastDeleted==lastNode){			//Konec subtree
			break;
		}
		if(citac%100==0&&lastDeleted==-1){		//Udelano dost prace je treba zkontrolovat zpravy
			return;
		}
		if(lastDeleted==-1){					// novy stav stav. prostoru?
			citac++;							// pocet udelane prace ++
			if(isClique(stack) == false){		// je aktualni stav klika?
					lastDeleted=stack->pull();
					continue;
			}
		}
		if(stack->getTop() == lastNode){		// jsme na vrcholu větve
			lastDeleted=stack->pull();
			continue;
		}
		
		if(stack->getTop() < lastNode){			// nejsme na vrcholu větve
			int toPush=lastDeleted;			
			if(toPush==-1){						// mame jit nahoru
				toPush=stack->getTop()+1;
				stack->push(toPush);
				lastDeleted=-1;	
			}else{								// prisli jsme zezhora
				if(++toPush>lastNode){			// jeste vice dolu
					lastDeleted=stack->pull();
				}else{							//do strany-nahoru
					stack->push(toPush);
					lastDeleted=-1;
				}
			}
			continue;
		}
	}
	WorkDone();
}



//Rozesle praci na zacatku
void ProblemSolver::sendWorkAtStart(){
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

//Nasloucha na zacatku
void ProblemSolver::listenAtStart(){
	int array[MPIHolder::getInstance().stackMaxSize];
	MPI_Status status;
	MPI_Recv(&array, MPIHolder::getInstance().stackMaxSize, MPI_INT, MPI_ANY_SOURCE, FLAG_JOB_SEND, MPI_COMM_WORLD, &status);
	stack = new Stack(array);
	endSize=stack->getSize();
	if(endSize>0)state=STATE_ACTIVE;
}

// Hlavní smycka
void ProblemSolver::startComputing(){		
	while(!terminate){
		switch(state){
			case STATE_ACTIVE:
				solveSubtree();
				checkMessages();
				break;
			case STATE_IDLE:
				tokenStart();
				if(!workRequestSent) getNewWork();
				checkMessages();
				break;
		}	
	}
}

//Prisel token
//TODO (je mozne posilat v tokenu celou maximalni kliku)
void ProblemSolver::Token(int * buffer){
	int myRank=MPIHolder::getInstance().myRank;
	if(myRank==0){						// jsem P0
		if(buffer[0]==TOKEN_WHITE){ 	//skoncil aduv je treba sebrat vysledek
			terminate=true;
			maxCliqueID=buffer[2];
		}else{
			p0TokenSent=false;			// je treba zacit nove kolo
		}
		return;
	}
	
	if(state==STATE_ACTIVE){	// pokud pracuji jen ulozim token na pozdeji	
		token=buffer; 			
	}else{						// nepracuji, zpracuji token okamzite
		if(tokenColor==TOKEN_BLACK){
			buffer[0]=TOKEN_BLACK;			//obarvuji token
		}
		if(buffer[1]<maxClique.getSize()){	//kontroluju max Clique
			buffer[1]=maxClique.getSize();
			buffer[2]=MPIHolder::getInstance().myRank;
		}
		MPI_Send(buffer,MPIHolder::getInstance().stackMaxSize,MPI_INT,(myRank+1)%MPIHolder::getInstance().cpuCounter,FLAG_TOKEN,MPI_COMM_WORLD);
		tokenColor=TOKEN_WHITE;				//odeslal jsem token. Obarvím se.
		token=0;
	}
}

//Prisla zadost o praci
void ProblemSolver::JobRequest(int * buffer,int source){
	Stack * stackToSend = divideStack();	
	if(stackToSend==0){						// vyplati se predavat praci?
		int * array=new int[1];
		MPI_Send(array, 1, MPI_INT, source, FLAG_JOB_NONE, MPI_COMM_WORLD); //neposilam praci
	}else{
		MPI_Send( stackToSend->serialize(),MPIHolder::getInstance().stackMaxSize, MPI_INT,source,FLAG_JOB_SEND,MPI_COMM_WORLD); // posilam praci
		if(source<MPIHolder::getInstance().myRank){ 		// posilam procesoru mensimu nez ja
			tokenColor=TOKEN_BLACK;
		}
	}
}

//Byla nam pridelena nova prace
void ProblemSolver::JobReceived(int * buffer){
	state=STATE_ACTIVE;
	tokenColor=TOKEN_WHITE;
	stack = new Stack(buffer);
	endSize = stack->getSize();
	workRequestSent=false;
}

//Zadany procesor pro nas nema praci
void ProblemSolver::NoJobReceived(){
	workRequestSent=false;
}


//Rozdeli strom pokud je pocet uzlu ke zpracovani od toho uzlu 512 a vice a zaroven nejsem pocatecni uzel

//TODO proverit stack is empty
Stack * ProblemSolver::divideStack(){
	if(stack->getSize()==0) return 0;
	int lastNode=graph->size()-1;
	int pow = lastNode-stack->getTop();
	int cnt=1;
	Stack * toSend=0;
	for(int i=0;i<pow;i++){// 2^i, i je prislusny radek pascalova trojuh.
		cnt*=2;
	}
	if(cnt>500&&(stack->getSize()>endSize)){
		toSend= new Stack(stack->serialize());
		int lastDeleted=stack->pull();
		stack->push(lastDeleted+1);
	}	
	return toSend;
}


// Zada o novou praci
Stack * ProblemSolver::getNewWork(){
	int askerId = askerID();
    int buffer[MPIHolder::getInstance().stackMaxSize];
	MPI_Send(new int[MPIHolder::getInstance().stackMaxSize],MPIHolder::getInstance().stackMaxSize, MPI_INT,askerID(),FLAG_JOB_REQUEST,MPI_COMM_WORLD);
	workRequestSent=true;
}

// Kontroluje zpravy a reaguje na ne
void ProblemSolver::checkMessages(){
	int flag;
	MPI_Status status;
	while(true){
		MPI_Iprobe(MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &flag, &status);
		if(flag==0) return; 						// neni zadna zprava
		int buffer[MPIHolder::getInstance().stackMaxSize];
		MPI_Recv(&buffer, MPIHolder::getInstance().stackMaxSize, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
		switch(status.MPI_TAG){						// na zaklade tagu se rozhoduje o co se jedna
			case FLAG_TOKEN:		//Prisel token
				Token(buffer);
				break;
			case FLAG_JOB_REQUEST: 	//nekdo zada o praci
				JobRequest(buffer,status.MPI_SOURCE);
				break;
			case FLAG_JOB_SEND: 	// prisla prace 
				//cout<<"CPU:"<<MPIHolder::getInstance().myRank<<" dostal praci od "<<status.MPI_SOURCE<<endl;
				JobReceived(buffer);
				break;
			case FLAG_JOB_NONE: 	// neni prace
				NoJobReceived();
				break;
			case FLAG_GET_CLIQUE:	// mam nejvetsi kliku, prisla zadost o uzly
				SendClique();
				break;
			case FLAG_TERMINATE:	// ukonci se
				terminate=true;
		}
	}
}


//Je dany stav na zasobniku klika?
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

// zastarale - pouzivalo se v seriove verzi --> pouzivam pro vypis z p0
void ProblemSolver::printMaxClique(){
	cout << "MaxClique size: " << this->maxClique.getSize() << endl;
	this->maxClique.printArrayNodes();
	cout <<"Process: "<<MPIHolder::getInstance().myRank<<endl;
}


// Algoritmus hledani darce (lokalni citac)
int ProblemSolver::askerID(){
	lastAsked = (lastAsked+1) % (MPIHolder::getInstance().cpuCounter);
	if(lastAsked==MPIHolder::getInstance().myRank){
		lastAsked = (lastAsked+1) % (MPIHolder::getInstance().cpuCounter);
	}
	return lastAsked;	
}

//P0 sebere vysledky vypne ostatni procesy a vypise vysledek
void ProblemSolver::printResults(){
	if(MPIHolder::getInstance().myRank!=0)return;;
	MPI_Status status;

	if(maxCliqueID==0){
		printMaxClique();
	}else{
		int * array = new int[MPIHolder::getInstance().stackMaxSize];
		MPI_Send(0,0,MPI_INT,maxCliqueID,FLAG_GET_CLIQUE,MPI_COMM_WORLD);
		MPI_Recv(array,MPIHolder::getInstance().stackMaxSize, MPI_INT, maxCliqueID, FLAG_GET_CLIQUE, MPI_COMM_WORLD, &status);
		int size=array[0];
		cout<<"MaxClique size:"<< size<<endl<<"Nodes: ";
		for(int i=1;i<=size;i++){
			cout<<array[i]<<" ";
		}
		cout<<endl<<"Process: "<<maxCliqueID<<endl;
	}
	for(int i=1;i<MPIHolder::getInstance().cpuCounter;i++){
		MPI_Send(0,0,MPI_INT,i,FLAG_TERMINATE,MPI_COMM_WORLD);
	}
}

// P0 zacina ADUV
void ProblemSolver::tokenStart(){
	int myRank=MPIHolder::getInstance().myRank;
	if(myRank!=0) return;
	if(!p0TokenSent){
		int * token = MPIHolder::getInstance().getTokenArray(TOKEN_WHITE,maxClique.getSize(),0);
		p0TokenSent=true;
		MPI_Send(token,MPIHolder::getInstance().stackMaxSize,MPI_INT,1,FLAG_TOKEN,MPI_COMM_WORLD);
	}
}

// Zasle kliku procesoru 0
void ProblemSolver::SendClique(){
	int * array = maxClique.serialize();
	MPI_Send(array,MPIHolder::getInstance().stackMaxSize,MPI_INT,0,FLAG_GET_CLIQUE,MPI_COMM_WORLD);
}
