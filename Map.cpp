#include "Map.h"

Map::Map(int** map, int id, bool mirrored)
{
	this->id = id;
	this->mirrored = mirrored;

	this->spawnEnemies = new point[ENEMYSPAWN];
	this->numSpawnEnemies = 0;
	//this->spawnFlyingEnemies = new point[ENEMYSPAWN];
	//this->numSpawnFlyingEnemies = 0;

	this->spawnItem = new point;
	this->itemPicked = false;

	this->map = new int*[ROW];
	for (int i = 0; i < ROW; i++)
	{
		this->map[i] = new int[COLUMN];
		for (int j = 0; j < COLUMN; j++)
		{
			this->map[i][j] = map[i][j];

			if (map[i][j] == ENEMYMAPCHARACTER || map[i][j] == FLYINGMAPCHARACTER) //spawn nemici
			{
				this->spawnEnemies[numSpawnEnemies].x = j + 1;
				this->spawnEnemies[numSpawnEnemies].y = i + 1;
				numSpawnEnemies++;
			}
			/*else if (map[i][j] == FLYINGMAPCHARACTER) //spawn nemici volanti
			{
				//this->spawnFlyingEnemies[numSpawnFlyingEnemies].x = j + 1;
				//this->spawnFlyingEnemies[numSpawnFlyingEnemies].y = i + 1;
				//numSpawnFlyingEnemies++;
				this->spawnEnemies[numSpawnEnemies].x = j + 1;
				this->spawnEnemies[numSpawnEnemies].y = i + 1;
				numSpawnEnemies++;
			}*/
			else if (map[i][j] == ITEMMAPCHARACTER) //spawn oggetto
			{
				this->spawnItem->x = j + 1;
				this->spawnItem->y = i + 1;
			}
		}
	}

	this->prev = NULL;
	this->next = NULL;
}

Map::Map(Map* m)
{
	this->id = m->GetID();
	this->mirrored = m->GetMirrored();

	this->spawnEnemies = m->GetSpawnEnemies();
	this->numSpawnEnemies = m->GetNumSpawnEnemies();
	//this->spawnFlyingEnemies = m->GetSpawnFlyingEnemies();	
	//this->numSpawnFlyingEnemies = m->GetNumSpawnFlyingEnemies();

	this->itemDrop = m->GetItemDrop();
	this->spawnItem = m->GetSpawnItem();
	this->itemPicked = m->GetItemPicked();

	this->map = m->GetMap();

	this->prev = NULL;
	this->next = NULL;
}

int Map::GetID() { return this->id; }
void Map::SetID(int i) { this->id = i; }

bool Map::GetMirrored() { return this->mirrored; }
void Map::SetMirrored(bool m) { this->mirrored = m; }

int** Map::GetMap() { return this->map; }
void Map::SetMap(int** m) { this->map = m; }

point* Map::GetSpawnEnemies() { return this->spawnEnemies; }
void Map::SetSpawnEnemies(point* se) { this->spawnEnemies = se; }

int Map::GetNumSpawnEnemies() { return this->numSpawnEnemies; }
void Map::SetNumSpawnEnemies(int n) { this->numSpawnEnemies = n; }

//point* Map::GetSpawnFlyingEnemies() { return this->spawnFlyingEnemies; }
//void Map::SetSpawnFlyingEnemies(point* se) { this->spawnFlyingEnemies = se; }

//int Map::GetNumSpawnFlyingEnemies() { return this->numSpawnFlyingEnemies; }
//void Map::SetNumSpawnFlyingEnemies(int n) { this->numSpawnFlyingEnemies = n; }

OggettoMappa* Map::GetItemDrop() { return this->itemDrop; }
void Map::SetItemDrop(OggettoMappa* i) { this->itemDrop = i; }

point* Map::GetSpawnItem() { return this->spawnItem; }

bool Map::GetItemPicked() { return this->itemPicked; }
void Map::SetItemPicked(bool ip) { this->itemPicked = ip; }

Map* Map::GetPrev() { return this->prev; }
void Map::SetPrev(Map* p) { this->prev = p; }

Map* Map::GetNext() { return this->next; }
void Map::SetNext(Map* n) { this->next = n; }