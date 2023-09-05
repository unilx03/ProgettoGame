/*----------------------------------------------------------------------------------
I nemici vengono gestiti per mezzo di una lista dinamica.
----------------------------------------------------------------------------------*/

#include <ncurses/ncurses.h>
#include "FlyingEnemyX.h"
#include <algorithm>    // std::random_shuffle


const int NUM_ENEMIES_DEFAULT = 3; //numero di nemici presenti di default sulla mappa
const int NUM_ENEMIES_GROWTH = 2; //numero di livelli di difficoltà necessari per aumentare il numero di nemici di 1

struct nodo{    
    Enemy *e;
    bool is_dead;
    nodo *next;
};
typedef nodo* p_nodo;

//Inserisce un nuovo nemico in testa alla lista.
p_nodo head_insert(p_nodo h, WINDOW * playwin, int y, int x, MapManager* map, int enemy_type);
//Stampa sulla mappa tutti 3 nemici istanziati.
void display_list(p_nodo h);
//Fa muovere tutti i nemici nella lista di un "passo", in base alla funzione di movimento associata a ciascuna tipologia.
p_nodo action_list(WINDOW * playwin, p_nodo h, Hero* player);
//Setta le statistiche dei nemici (attacco, vita, etc.) in base al livello di difficoltà di gioco attuale.
void set_enemies_stats(p_nodo h, int diff_level);
//Prende in input il numero di nemici da generare e restituisce una lista di nemici con le loro coordinate sulla mappa.
p_nodo generate_enemies(WINDOW * playwin, MapManager* map, int diff_level);

void scriviEnemy(ofstream &file, Enemy *enemy);
void leggiEnemy(ifstream &file, Enemy *enemy);
void salvaListaSuFile(p_nodo h, const string &nomeFile);
p_nodo leggiListaDaFile(const string &nomeFile);