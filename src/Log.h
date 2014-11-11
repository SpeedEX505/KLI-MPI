#ifndef Log_H
#define Log_H


class Log {
private:
public:
	/*
	 * Zapis informaci do souboru, ktery rank co zapsal
	 * @param outToFile Obsah, ktery se ma zapsat
	 */
	static void logToFile(string outToFile);
};

#endif