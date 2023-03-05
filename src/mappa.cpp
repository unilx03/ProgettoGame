#include "mappa.h"

void letturaFile()
{
	ifstream inputFile; /* Dichiarazione di tipo */
	inputFile.open("file.txt");
	char ch;
	/* lettura dati */
	while(!inputFile.eof()){
		inputFile.get(ch);
		cout << ch << endl;
	}
	inputFile.close();
}

void scritturaFile()
{


	ofstream outputFile; /* Dichiarazione di tipo */
	outputFile.open("file.txt"); /* Apertura del file */
	outputFile << "Prova di scrittura su file";
	outputFile.close();
}


