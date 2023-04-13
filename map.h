#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <ncurses.h>

using namespace std;

#define ROW 20
#define COLUMN 160

#define ENEMYSPAWN 100 //numero massimo di nemici e oggetti che possono essere generati
#define ITEMSPAWN 3

#define ENEMYMAPNUMBER 3 //carattere che indica uno spawn di nemici o oggetti nella mappa
#define ITEMMAPNUMBER 5

struct point{
    int x;
    int y;
};

struct level{
    int map[COLUMN][ROW];
	
    point spawnEnemies[ENEMYSPAWN];
	int numSpawnEnemies;
	point positionEnemies[ENEMYSPAWN];
	int numPositionEnemies;
	
    point spawnItems[ITEMSPAWN];
	int numSpawnItems;
	point positionItems[ITEMSPAWN];
	int numPositionItems;
	
	level* prec;
    level* next;
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
void saveLoadedMaps(punt_level tail);

punt_level initializeLevelList(punt_level head);
void drawMap(WINDOW* win, punt_level l);