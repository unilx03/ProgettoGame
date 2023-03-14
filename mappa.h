#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <ncurses.h>

using namespace std;

struct punto{
    int x;
    int y;
};

struct livello{
    int mappa[80][20];
    punto spawnNemici[100];
	int numSpawnNemici;
    punto spawnOggetti[3];
	int numSpawnOggetti;
    livello* next;
};
typedef livello* punt_livello;

punt_livello aggiungiLivello (punt_livello head, punt_livello liv);
void stampaLivelli(punt_livello head);

punt_livello inizializzaListaLivelli(punt_livello head);
void disegnaMappa(WINDOW* win, punt_livello l);