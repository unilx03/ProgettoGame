#include "MapList.h"

MapList::MapList()
{
    this->tail = NULL;
}

Map* MapList::GetTail() { return this->tail; }
void MapList::SetTail(Map* t) { this->tail = t; }

void MapList::addMap(Map* node)
{
    Map* temp = new Map(node);

	if (this->tail != NULL)
		this->tail->SetNext(temp);
    temp->SetPrev(this->tail);
    temp->SetNext(NULL);

    this->SetTail(temp);
}

Map* MapList::loadMapFromID (Map* t, int id)
{
    if (id == 0)
	{
		return t;
	}
	else
	{
		return loadMapFromID (t->GetPrev(), id - 1);
	}
}

int MapList::countMaps(Map* t)
{
	if (t == NULL)
		return 0;
	else
		return 1 + countMaps(t->GetPrev());
}

void MapList::nextMap()
{
    this->SetTail(this->tail->GetNext());
}

void MapList::previousMap()
{
    if (this->tail->GetPrev() != NULL)
		this->SetTail(this->tail->GetPrev());
}

void MapList::printMaps(Map* t)
{
	if (t != NULL)
	{
		cout << t->GetID() << endl;
		cout << t->GetMirrored() << endl << endl;

		for (int i = 0; i < ROW; i++)
		{
			for (int j = 0; j < COLUMN; j++)
			{
				cout << t->GetMap()[i][j];
			}
			cout << endl;
		}
		
		if (t->GetPrev() != NULL)
			cout << "Ha precedente" << endl;
		else
			cout << "Non ha precedente" << endl;
		
		if (t->GetNext() != NULL)
			cout << "Ha successivo" << endl;
		else
			cout << "Non ha successivo" << endl;

		cout << endl;
		for (int i = 0; i < t->GetNumSpawnEnemies(); i++)
		{
			cout << "Enemy: " << t->GetSpawnEnemies()[i].x << " / " << t->GetSpawnEnemies()[i].y << endl;
		}
		cout << endl;
		for (int i = 0; i < t->GetNumSpawnItems(); i++)
		{
			cout << "Item: " << t->GetSpawnItems()[i].x << " / " << t->GetSpawnItems()[i].y << endl;
		}
		cout << endl;
		
		cout << endl << endl;
		printMaps(t->GetPrev());
	}
}