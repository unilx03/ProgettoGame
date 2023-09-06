#include "MapManager.h"

MapManager::MapManager(WINDOW* win)
{
    this->window = win;
    InitializeFullMapList();
    this->currentMapList = new MapList();

	this->itemList = new OggettoMappa*[8];
    this->itemList[0] = new OggettoMappa("Healing Carrot", "<3", 1, "Health");
    this->itemList[1] = new OggettoMappa("Carrot Sword", "=>", 0.35, "Strenght");
    this->itemList[2] = new OggettoMappa("Carrot Shield", "|)", 1.0, "Defense");
    this->itemList[3] = new OggettoMappa("Greedy Carrot", "$$", 0.5, "Double Money",0, 0, true);
    this->itemList[4] = new OggettoMappa("Carrot Points", "##", 0.5, "Double Score",0, 0, true);
    this->itemList[5] = new OggettoMappa("Magic Carrot", "|3", 1.0, "Invincibility",0, 0, true);
    this->itemList[6] = new OggettoMappa("Bouncing Carrot", "|7", 1.0, "Jump Force");
    this->itemList[7] = new OggettoMappa("Sale", "-!", 0.2, "Sale",0, 0, false, true);
}

void MapManager::InitializeFullMapList()
{
    this->fullMapList = new MapList();

    ifstream inputFile; //Dichiarazione di tipo
	char path[100] = "map.txt";
	inputFile.open(path);

	int id = 0;
	if(!inputFile.fail())
	{
		while (!inputFile.eof())
		{
            int** map = new int*[ROW];
            int** mirroredMap = new int*[ROW];
			for (int i = 0; i < ROW; i++)
			{
				map[i] = new int[COLUMN];
				mirroredMap[i] = new int[COLUMN];
				for (int j = 0; j < COLUMN; j++)
				{
					int mapPoint;
					inputFile >> mapPoint;
					
					map[i][j] = mapPoint;
                    mirroredMap[i][COLUMN - j - 1] = mapPoint;
				}
			}

            Map* m1 = new Map(map, id, false);
            id++;
			Map* m2 = new Map(mirroredMap, id, true);
            id++;

			this->fullMapList->AddMap(m1);
			this->fullMapList->AddMap(m2);
		}

		this->fullMapList->SetTail(this->fullMapList->GetTail()->GetPrev()); //il ciclo while crea un livello vuoto in più in fondo
		this->fullMapList->SetTail(this->fullMapList->GetTail()->GetPrev());
	}

    this->numMaps = this->fullMapList->CountMaps(fullMapList->GetTail());
	inputFile.close();
}

WINDOW* MapManager::GetWindow() { return this->window; }
void MapManager::SetWindow(WINDOW* w) { this->window = w; }

MapList* MapManager::GetFullMapList() { return this->fullMapList; }
void MapManager::SetFullMapList(MapList* fml) { this->fullMapList = fml; }

int MapManager::GetNumMaps() { return this->numMaps; }
void MapManager::SetNumMaps(int nm) { this->numMaps = nm; }

MapList* MapManager::GetCurrentMapList() { return this->currentMapList; }
void MapManager::SetCurrentMapList(MapList* cml) { this->currentMapList = cml; }

void MapManager::GenerateNewMap(bool lucky)
{
    int levelToLoadID = rand() % numMaps;
	if (this->currentMapList->GetTail() != NULL && this->currentMapList->GetTail()->GetPrev() != NULL)
	{
		if (levelToLoadID == this->currentMapList->GetTail()->GetPrev()->GetID())
		{
			levelToLoadID += 2;
			if (levelToLoadID >= (this->numMaps * 2))
				levelToLoadID -= (this->numMaps * 2);
		}
	}

    this->currentMapList->AddMap(this->fullMapList->LoadMapFromID(this->fullMapList->GetTail(), levelToLoadID));
	this->currentMapList->GetTail()->SetItemDrop(GenerateDrop(this->itemList, lucky));
}

void MapManager::DrawCurrentMap()
{
	box(this->window, 0, 0);
	wclear(this->window);

	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COLUMN; j++)
		{
			char character = ' ';
			if (this->currentMapList->GetTail()->GetMap()[i][j] == EMPTYCHARACTER)
				character = ' ';
			else if (this->currentMapList->GetTail()->GetMap()[i][j] == FLOORCHARACTER)
				character = '_';
			else if (this->currentMapList->GetTail()->GetMap()[i][j] == WALLCHARACTER)
				character = '|';
			else
				character = ' ';
			mvwprintw(this->window, i + 1, j + 1, "%c", character);
		}
	}

	//per disegnare l'oggetto
	if (!this->currentMapList->GetTail()->GetItemPicked())
		mvwprintw(this->window, this->currentMapList->GetTail()->GetItemDrop()->getYOgg(), this->currentMapList->GetTail()->GetItemDrop()->getXOgg(), this->currentMapList->GetTail()->GetItemDrop()->getSkin());

	wrefresh(this->window);
}

OggettoMappa* MapManager::GenerateDrop(OggettoMappa* item[], bool lucky)
{
	OggettoMappa * p = new OggettoMappa(chosenObject(item, lucky));
	
	int x = this->GetCurrentMapList()->GetTail()->GetSpawnItem()->x;
    p->setXOgg(x);
    int y = this ->GetCurrentMapList()->GetTail()->GetSpawnItem()->y;
	p->setYOgg(y);
	return p;
}