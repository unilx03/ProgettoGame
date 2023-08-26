#include "Map.h"

Map::Map(int** map, int id, bool mirrored)
{
	this->id = id;
	this->mirrored = mirrored;

	this->numSpawnEnemies = 0;
	this->spawnEnemies = new point[ENEMYSPAWN];
	this->numSpawnItems = 0;
	this->spawnItems = new point[ITEMSPAWN];

	this->numPositionEnemies = 0;
	this->positionEnemies = new point[ENEMYSPAWN];
	this->numPositionItems = 0;
	this->positionItems = new point[ITEMSPAWN];

	this->map = new int*[ROW];
	for (int i = 0; i < ROW; i++)
	{
		this->map[i] = new int[COLUMN];
		for (int j = 0; j < COLUMN; j++)
		{
			this->map[i][j] = map[i][j];

			if (map[i][j] == ENEMYMAPNUMBER) //spawn nemici livello normale
			{
				this->spawnEnemies[numSpawnEnemies].x = j + 1;
				this->spawnEnemies[numSpawnEnemies].y = i + 1;
				this->numSpawnEnemies++;
			}
			else if (map[i][j] == ITEMMAPNUMBER) //spawn oggetti livello normale
			{
				this->spawnItems[numSpawnItems].x = j + 1;
				this->spawnItems[numSpawnItems].y = i + 1;
				this->numSpawnItems++;
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

	this->numSpawnEnemies = m->GetNumSpawnEnemies();
	this->spawnEnemies = m->GetSpawnEnemies();
	this->numSpawnItems = m->GetNumSpawnItems();
	this->spawnItems = m->GetSpawnItems();

	this->numPositionEnemies = m->GetNumPositionEnemies();
	this->positionEnemies = m->GetPositionEnemies();
	this->numPositionItems = m->GetNumPositionItems();
	this->positionItems = m->GetPositionItems();

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

point* Map::GetPositionEnemies() { return this->positionEnemies; }
void Map::SetPositionEnemies(point* pe) { this->positionEnemies = pe; }

int Map::GetNumPositionEnemies() { return this->numPositionEnemies; }
void Map::SetNumPositionEnemies(int n) { this->numPositionEnemies = n; }

point* Map::GetSpawnItems() { return this->spawnItems; }
void Map::SetSpawnItems(point* si) { this->spawnItems = si; }

int Map::GetNumSpawnItems() { return this->numSpawnItems; }
void Map::SetNumSpawnItems(int n) { this->numSpawnItems = n; }

point* Map::GetPositionItems() { return this->positionItems; }
void Map::SetPositionItems(point* pi) { this->positionItems = pi; }

int Map::GetNumPositionItems() { return this->numPositionItems; }
void Map::SetNumPositionItems(int n) { this->numPositionItems = n; }

Map* Map::GetPrev() { return this->prev; }
void Map::SetPrev(Map* p) { this->prev = p; }

Map* Map::GetNext() { return this->next; }
void Map::SetNext(Map* n) { this->next = n; }

/*void Map::GenerateEnemies ()
{
	//numPositionEnemies = rand() % ENEMYSPAWN;
	numPositionEnemies = 0;
	for (int i = 0; i < numPositionEnemies; i++)
	{
		int randomEnemy = rand() % numSpawnEnemies;
		positionEnemies[i].x = spawnEnemies[randomEnemy].x;
		positionEnemies[i].y = spawnEnemies[randomEnemy].y;
	}
}*/

void Map::GenerateItems ()
{
	//numPositionItems = rand() % ITEMSPAWN;
	numPositionItems = 0;
	for (int i = 0; i < numPositionItems; i++)
	{
		int randomItem = rand() % numSpawnItems;
		positionItems[i].x = spawnItems[randomItem].x;
		positionItems[i].y = spawnItems[randomItem].y;
	}
}
