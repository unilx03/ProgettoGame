#include <iostream>
#include <fstream>
using namespace std;

// Funzione per salvare la lista 'h' in un file binario con un numero identificativo
void salvaListaSuFile(Nodo *h, int numeroLista, const string &nomeFile) {
    ofstream file(nomeFile,ios::binary);

    if (!file.is_open()) {
        cerr << "Impossibile aprire il file." << endl;
        return;
    }

    // Scrivi il numero identificativo della lista
    file.write(reinterpret_cast<char *>(&numeroLista), sizeof(int));

    Nodo *current = h;

    while (current != nullptr) {
        // Scrivi il puntatore Enemy 'e' nell'array di caratteri come rappresentazione binaria
        file.write(reinterpret_cast<char *>(current->e), sizeof(Enemy));

        // Scrivi l'indirizzo del prossimo nodo 'next' nell'array di caratteri
        file.write(reinterpret_cast<char *>(&current->next), sizeof(Nodo *));

        current = current->next;
    }

    file.close();
}

// Funzione per leggere una lista specifica dal file binario in base al numero identificativo
Nodo *leggiListaDaFile(int numeroLista, const string &nomeFile) {
    ifstream file(nomeFile, std::ios::binary);

    if (!file.is_open()) {
        cerr << "Impossibile aprire il file." << endl;
        return nullptr;
    }

    Nodo *h = nullptr;
    Nodo *current = nullptr;

    while (true) {
        int listaNumero;
        // Leggi il numero identificativo della lista
        file.read(reinterpret_cast<char *>(&listaNumero), sizeof(int));

        // Se siamo alla fine del file, esci dal ciclo
        if (file.eof()) {
            break;
        }

        // Leggi il puntatore Enemy 'e' dall'array di caratteri
        Enemy *enemy = new Enemy;
        file.read(reinterpret_cast<char *>(enemy), sizeof(Enemy));

        // Leggi l'indirizzo del prossimo nodo 'next' dall'array di caratteri
        Nodo *next = nullptr;
        file.read(reinterpret_cast<char *>(&next), sizeof(Nodo *));

        // Se il numero identificativo corrisponde, crea un nuovo nodo e aggiungilo alla lista
        if (listaNumero == numeroLista) {
            Nodo *nodo = new Nodo;
            nodo->e = enemy;
            nodo->next = next;

            if (h == nullptr) {
                h = nodo;
            }

            if (current != nullptr) {
                current->next = nodo;
            }

            current = nodo;
        } else {
            // Altrimenti, ignoriamo questo blocco di dati nel file
            delete enemy;
            if (next != nullptr) {
                delete next;
            }
        }
    }

    file.close();
    return h;
}
