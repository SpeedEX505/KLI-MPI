#ifndef MPIHolder_H
#define MPIHolder_H

#define FLAG_GET_JOB 100
#define FLAG_SEND_JOB 101
#define FLAG_JOB_ACCEPTED 102
#define FLAG_NO_JOB 103

class MPIHolder{
	public:
	static MPIHolder& getInstance(){
		static MPIHolder instance;
		return instance;
	}
	int myRank;
	int cpuCounter;
	int stackMaxSize;

	private:
	MPIHolder(){};
 	MPIHolder(MPIHolder const&);	 // Don't Implement
        void operator=(MPIHolder const&);// Don't implement
	static MPIHolder * instance;
};
#endif
