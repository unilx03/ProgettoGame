#include <iostream>
#include <fstream>
using namespace std;

void salvoNemiciFile(p_nodo h, int level, const string& filename) {
    ofstream outputFile(filename);

    if (!outputFile.is_open()) {
        cerr << "Impossibile aprire il file " << filename <<endl;
        return;
    }

    p_nodo current = h;

    while (current != nullptr) {
        // Scrivi il livello e le informazioni dell'enemy nel file
        outputFile <<  level << endl;
        outputFile <<  current->e.yLoc <<endl;
        outputFile <<  current->e.xLoc <<endl;
        outputFile <<  current->e.enemy_type <<endl;
        outputFile <<  current->e.health <<endl;
        outputFile <<  current->e.strength << std::endl;
        outputFile <<  current->e.defense << endl;
        outputFile <<  current->e.score_released <<endl;
        outputFile <<  current->e.money_released << endl;
        outputFile <<  current->e.is_left << endl;


        // Vai al prossimo nodo
        current = current->next;
    }

    outputFile.close();
}

p_nodo creoListaNuova(int level, const string& filename) {
     ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        cerr << "Impossibile aprire il file " << filename << endl;
        return 1; // Uscita con errore
    }

    string line;
    int value[50];

    while(getline(inputFile, line){
        if (stoi(line) == level) {
             //controllo se è il livello desiderato
             for(int j=0;j<8;j++){
             getline(inputFile, line);
             value[j] = stoi(line);
             }
             getline(inputFile, line);
             int boolvalue=(line == "true");
           //funzione di Bea p_nodo = new Enemy(value[0], .., valueBool, vALUE[5]);
        }
        else{
             for(int j=0;j<8;j++){
                 getline(inputFile, line);
             }
        }
    }

    return h;

}
