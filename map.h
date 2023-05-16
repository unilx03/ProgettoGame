#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <ncurses.h>

using namespace std;

#define ROW 20
#define COLUMN 160

#define ENEMYSPAWN 30 //numero massimo di nemici e oggetti che possono essere generati
#define ITEMSPAWN 1

#define ENEMYMAPNUMBER 3 //carattere che indica uno spawn di nemici o oggetti nella mappa
#define ITEMMAPNUMBER 5

struct point{
    int x;
    int y;
};

struct level{
	int id; //id mappa
	bool mirrored; //e' specchiato?
    int map[COLUMN][ROW]; //caselle mappa segnate come in map.txt

    point spawnEnemies[ENEMYSPAWN]; //punti possibili di spawn dei nemici presi dalla mappa
	int numSpawnEnemies; //numero massimo di spawn nemici presenti nella mappa
	point positionEnemies[ENEMYSPAWN]; //punti di spawn effettivi dei nemici
	int numPositionEnemies; //numero effettivo di nemci
	
    point spawnItems[ITEMSPAWN]; //analogo ai nemici
	int numSpawnItems;
	point positionItems[ITEMSPAWN];
	int numPositionItems;
	
	level* prec; //livello precedente
    level* next; //livello successivo
};
typedef level* punt_level;

//Funzioni di gestione livelli
//punt_livello aggiungiLivelloTesta (punt_livello head, punt_livello liv);
punt_level addLevel (punt_level node, punt_level liv);
punt_level loadMapFromID (punt_level tail, int id);
int countLevels(punt_level tail);

punt_level nextLevel (punt_level node);
punt_level previousLevel (punt_level node);
punt_level generateEnemies (punt_level node);
punt_level generateItems (punt_level node);

//Funzioni di Debug
void printLevels(punt_level tail);

//Funzioni di salvataggio riguardo i livelli
punt_level loadSavedMaps(punt_level levelList, punt_level tail);

punt_level initializeLevelList(punt_level head);
void drawMap(WINDOW* win, punt_level l);