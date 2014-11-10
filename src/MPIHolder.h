#ifndef MPIHolder_H
#define MPIHolder_H

#define FLAG_JOB_REQUEST 100
#define FLAG_JOB_SEND 101
#define FLAG_JOB_NONE 102
#define FLAG_TOKEN 103
#define FLAG_FINISH 104

class MPIHolder{
	public:
	static MPIHolder& getInstance(){
		static MPIHolder instance;
		return instance;
	}
	int myRank;
	int cpuCounter;
	int stackMaxSize;
	int * getTokenArray(int tokenColor, int maxClique, int cpuWithMaxClique){
		int * array = new int [stackMaxSize];
		array[0]=tokenColor;
		array[1]=maxClique;
		array[2]=cpuWithMaxClique;
	}
	private:
	MPIHolder(){};
 	MPIHolder(MPIHolder const&);	 // Don't Implement
        void operator=(MPIHolder const&);// Don't implement
	static MPIHolder * instance;
};
#endif
