#ifndef Log_H
#define Log_H

#include <string>

class Log {
private:
	int mpiRank;
	string fileName;
public:
	Log();
	void logToFile();
};

#endif