#include "MapList.h"

MapList::MapList()
{
    this->tail = NULL;
}

Map* MapList::GetTail() { return this->tail; }
void MapList::SetTail(Map* t) { this->tail = t; }

void MapList::AddMap(Map* node)
{
    Map* temp = new Map(node);

	if (this->tail != NULL)
		this->tail->SetNext(temp);
    temp->SetPrev(this->tail);
    temp->SetNext(NULL);

    this->SetTail(temp);
}

Map* MapList::LoadMapFromID (Map* t, int id)
{
    if (id == 0)
		return t;
	else
		return LoadMapFromID (t->GetPrev(), id - 1);
}

int MapList::CountMaps(Map* t)
{
	if (t == NULL)
		return 0;
	else
		return 1 + CountMaps(t->GetPrev());
}

void MapList::NextMap()
{
    this->SetTail(this->tail->GetNext());
}

void MapList::PreviousMap()
{
    if (this->tail->GetPrev() != NULL)
		this->SetTail(this->tail->GetPrev());
}