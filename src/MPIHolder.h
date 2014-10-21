#ifndef MPIHolder_H
#define MPIHolder_H


class MPIHolder{
	public:
	static MPIHolder& getInstance(){
		static MPIHolder instance;
		return instance;
	}
	int myRank;
	int cpuCounter;

	private:
	MPIHolder();
 	MPIHolder(MPIHolder const&);	 // Don't Implement
        void operator=(MPIHolder const&);// Don't implement
	static MPIHolder * instance;
};
#endif
