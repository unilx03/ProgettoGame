#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <ncurses/ncurses.h>
#include "Drop.h"

using namespace std;

#define ROW 20
#define COLUMN 160

#define EMPTYCHARACTER 0
#define WALLCHARACTER 2
#define FLOORCHARACTER 1

#define ENEMYSPAWN 30 //numero massimo di nemici e oggetti che possono essere generati

#define ENEMYMAPCHARACTER 3 //carattere che indica uno spawn di nemici o oggetti nella mappa
#define FLYINGMAPCHARACTER 4
#define ITEMMAPCHARACTER 9

struct point{
    int x;
    int y;
};

class Map 
{
	protected:
		int id; //id mappa
		bool mirrored; //e' specchiato?
    	int** map; //caselle mappa segnate come in map.txt

    	point* spawnEnemies; //punti possibili di spawn dei nemici presi dalla mappa
		int numSpawnEnemies; //numero di spawn nemici
		point* spawnFlyingEnemies; //punti possibili di spawn dei nemici volanti verticali
		int numSpawnFlyingEnemies; //numero di spawn nemici volanti
	
		OggettoMappa* itemDrop;
    	point* spawnItem; //punto di spawn oggetto
		bool itemPicked;

		Map* prev;
		Map* next;

	public:
		Map(int** map, int id, bool mirrored);
		Map(Map* m);

		int GetID();
		void SetID(int i);

		bool GetMirrored();
		void SetMirrored(bool m);

		int** GetMap();
		void SetMap(int** m);

		point* GetSpawnEnemies();
		void SetSpawnEnemies(point* se);

		int GetNumSpawnEnemies();
		void SetNumSpawnEnemies(int n);

		point* GetSpawnFlyingEnemies();
		void SetSpawnFlyingEnemies(point* se);

		int GetNumSpawnFlyingEnemies();
		void SetNumSpawnFlyingEnemies(int n);

		OggettoMappa* GetItemDrop();
		void SetItemDrop(OggettoMappa* i);

		point* GetSpawnItem();
		void SetSpawnItem(point* si);

		bool GetItemPicked();
		void SetItemPicked(bool ip);
		
		Map* GetPrev();
		void SetPrev(Map* p);

		Map* GetNext();
		void SetNext(Map* p);
};
