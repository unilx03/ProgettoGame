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
	punto posizioneNemici[100];
	int numPosizioneNemici;
	
    punto spawnOggetti[3];
	int numSpawnOggetti;
	punto posizioneOggetti[3];
	int numPosizioneOggetti;
	
	livello* prec;
    livello* next;
};
typedef livello* punt_livello;

//Funzioni di gestione livelli
//punt_livello aggiungiLivelloTesta (punt_livello head, punt_livello liv);
punt_livello aggiungiLivelloDopo (punt_livello nodo, punt_livello liv);
punt_livello caricaMappaDaID (punt_livello tail, int id);
int contaLivelli(punt_livello tail);

punt_livello livelloSuccessivo (punt_livello nodo);
punt_livello livelloPrecedente (punt_livello nodo);
punt_livello generaNemici (punt_livello nodo);
punt_livello generaOggetti (punt_livello nodo);

//Funzioni di Debug
void stampaLivelli(punt_livello tail);

//Funzioni di salvataggio riguardo i livelli
void salvaLivelliCaricati(punt_livello tail);

punt_livello inizializzaListaLivelli(punt_livello head);
void disegnaMappa(WINDOW* win, punt_livello l);