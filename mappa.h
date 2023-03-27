#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <ncurses.h>

using namespace std;

#define ROW 20
#define COLUMN 80

#define ENEMYSPAWN 100 //numero massimo di nemici e oggetti che possono essere generati
#define ITEMSPAWN 3

#define ENEMYMAPNUMBER 3 //carattere che indica uno spawn di nemici o oggetti nella mappa
#define ITEMMAPNUMBER 5

struct punto{
    int x;
    int y;
};

struct livello{
    int mappa[COLUMN][ROW];
	
    punto spawnNemici[ENEMYSPAWN];
	int numSpawnNemici;
	punto posizioneNemici[ENEMYSPAWN];
	int numPosizioneNemici;
	
    punto spawnOggetti[ITEMSPAWN];
	int numSpawnOggetti;
	punto posizioneOggetti[ITEMSPAWN];
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