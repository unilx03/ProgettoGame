#include <iostream>
#include <fstream>
using namespace std;

// Funzione per scrivere un oggetto Enemy nel file binario
void scriviEnemy(ofstream &file, Enemy *enemy) {
    file.write(reinterpret_cast<char *>(enemy), sizeof(Enemy));
}

// Funzione per leggere un oggetto Enemy dal file binario
void leggiEnemy(ifstream &file, Enemy *enemy) {
    file.read(reinterpret_cast<char *>(enemy), sizeof(Enemy));
}

// Funzione per salvare la lista 'h' in un file binario
void salvaListaSuFile(p_nodo *h, const string &nomeFile) {
    std::ofstream file(nomeFile, std::ios::binary);

    if (!file.is_open()) {
        std::cerr << "Impossibile aprire il file." << std::endl;
        return;
    }

    Nodo *current = h;

    while (current != nullptr) {
        // Scrivi il puntatore Enemy 'e' nel file
        scriviEnemy(file, current->e);

        // Scrivi il valore di is_dead nel file
        file.write(reinterpret_cast<char *>(&current->is_dead), sizeof(bool));

        // Scrivi l'indirizzo del prossimo nodo 'next' nel file
        file.write(reinterpret_cast<char *>(&current->next), sizeof(Nodo *));

        current = current->next;
    }

    file.close();
}

// Funzione per leggere la lista dal file binario
Nodo *leggiListaDaFile(const std::string &nomeFile) {
    std::ifstream file(nomeFile, std::ios::binary);

    if (!file.is_open()) {
        std::cerr << "Impossibile aprire il file." << std::endl;
        return nullptr;
    }

    Nodo *h = nullptr;
    Nodo *current = nullptr;

    while (true) {
        // Leggi un nuovo oggetto Enemy dal file
        Enemy *enemy = new Enemy;
        leggiEnemy(file, enemy);

        // Leggi il valore di is_dead dal file
        bool is_dead;
        file.read(reinterpret_cast<char *>(&is_dead), sizeof(bool));

        // Leggi l'indirizzo del prossimo nodo 'next' dal file
        Nodo *next = nullptr;
        file.read(reinterpret_cast<char *>(&next), sizeof(Nodo *));

        // Se siamo alla fine del file, esci dal ciclo
        if (file.eof()) {
            break;
        }

        // Crea un nuovo nodo e aggiungilo alla lista
        Nodo *nodo = new Nodo;
        nodo->e = enemy;
        nodo->is_dead = is_dead;
        nodo->next = next;

        if (h == nullptr) {
            h = nodo;
        }

        if (current != nullptr) {
            current->next = nodo;
        }

        current = nodo;
    }

    file.close();
    return h;
}

// Funzione per liberare la memoria della lista
void liberareLista(Nodo *h) {
    while (h != nullptr) {
        Nodo *temp = h;
        h = h->next;
        delete temp->e; // Libera la memoria dell'Enemy
        delete temp;    // Libera la memoria del Nodo
    }
}


// Funzione per scrivere un oggetto Enemy nel file binario
void scriviEnemy(std::ofstream &file, Enemy *enemy) {
    file.write(reinterpret_cast<char *>(enemy), sizeof(Enemy));
}

// Funzione per leggere un oggetto Enemy dal file binario
void leggiEnemy(std::ifstream &file, Enemy *enemy) {
    file.read(reinterpret_cast<char *>(enemy), sizeof(Enemy));
}
