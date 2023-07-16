#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <ncurses.h>

using namespace std;

#define ROW 20
#define COLUMN 160

#define WALLCHARACTER 2
#define FLOORCHARACTER 1

#define ENEMYSPAWN 30 //numero massimo di nemici e oggetti che possono essere generati
#define ITEMSPAWN 1

#define ENEMYMAPNUMBER 3 //carattere che indica uno spawn di nemici o oggetti nella mappa
#define FLYINGMAPNUMBER 4
#define ITEMMAPNUMBER 9

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
		int numSpawnEnemies; //numero massimo di spawn nemici presenti nella mappa
		point* positionEnemies; //punti di spawn effettivi dei nemici
		int numPositionEnemies; //numero effettivo di nemci
	
    	point* spawnItems; //analogo ai nemici
		int numSpawnItems;
		point* positionItems;
		int numPositionItems;

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

		point* GetPositionEnemies();
		void SetPositionEnemies(point* pe);

		int GetNumPositionEnemies();
		void SetNumPositionEnemies(int n);

		point* GetSpawnItems();
		void SetSpawnItems(point* si);

		int GetNumSpawnItems();
		void SetNumSpawnItems(int n);

		point* GetPositionItems();
		void SetPositionItems(point* pi);

		int GetNumPositionItems();
		void SetNumPositionItems(int n);

		Map* GetPrev();
		void SetPrev(Map* p);

		Map* GetNext();
		void SetNext(Map* p);

		void GenerateEnemies();
		void GenerateItems();
};
