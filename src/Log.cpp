#include "Log.h"
#include "MPIHolder.h"

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

// ------------------------------------------------------------------------------------------------
static void Log::logToFile(string outToFile){
	// nazev souboru
	stringstream ss;
	ss << MPIHolder::getInstance().myRank;
	string oufFileName = string(ss) + ".log";

	fstream fout;
	fout.open(outFileName, ios_base::out);
	fout.seekp(0, ios::end);	// nastavi zapisovaci ukazatel na konec
	fout << "MPIrank " << MPIHolder::getInstance().myRank << ": " << outToFile << endl;
	fout.close();
}
