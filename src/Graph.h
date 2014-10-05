#ifndef Graph_H
#define Graph_H
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <cstdlib>

/** Graf, ktery je uchovan pomoci matice sousednosti
 */
class Graph{
	unsigned long nodesCnt;
	int ** nodesMatrix;
	
	/** Precte z prvni radky (soubor) pocet uzlu
	 * @param file je nazev souboru
	 * @return pocet uzlu
	 */
	int readNodesCnt(const char * file); 		// reads number of nodes

	/** Vytvori + inicializuje matici
	 * @param file je nazev souboru
	 * @return matice sousednosti
	 */
	int ** readNodesMatrix(const char * file);	// reads nodes into matrix
public:
	Graph(const char * filename);
	~Graph();
	// number of nodes
	int size();
	// matrix
	void print();
	// are the node1 and node2 connected?
	bool isConnected(int node1, int node2);
};

#endif
