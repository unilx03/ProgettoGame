#include "MapManager.h"

MapManager::MapManager(WINDOW* win)
{
    this->window = win;
    InitializeFullMapList();
    this->currentMapList = new MapList();
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
		//head = head->prec; //il ciclo while crea un livello vuoto in più in fondo
		//head = head->prec;
		//head->next = NULL;

		this->fullMapList->SetTail(this->fullMapList->GetTail()->GetPrev()); //il ciclo while crea un livello vuoto in più in fondo
		this->fullMapList->SetTail(this->fullMapList->GetTail()->GetPrev());
		//this->fullMapList->GetTail()->SetNext(NULL);
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

void MapManager::GenerateNewMap()
{
    int levelToLoadID = rand() % numMaps;
    this->currentMapList->AddMap(this->fullMapList->LoadMapFromID(this->fullMapList->GetTail(), levelToLoadID));
	//GenerateDrop();
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
				character = '-';
			else if (this->currentMapList->GetTail()->GetMap()[i][j] == WALLCHARACTER)
				character = '|';
			else
				character = ' ';
			mvwprintw(this->window, i + 1, j + 1, "%c", character);
		}
	}

	//per disegnare l'oggetto
	//if (!this->currentMapList->GetTail()->GetItemPicked())
	//	mvwprintw(this->window, this->currentMapList->GetTail()->GetItemDrop()->getYOgg(), this->currentMapList->GetTail()->GetItemDrop()->getXOgg(), this->currentMapList->GetTail()->GetItemDrop() -> getSkin());

	wrefresh(this->window);
}

/*
Oltre alle informazioni relative ad ogni livello, salvare il numero di livelli caricati e statistiche del protagonista
*/

void MapManager::LoadSavedMaps()
{
	ifstream inputFile; /* Dichiarazione di tipo */
	char path[100] = "mapSaveFile.txt";
	inputFile.open(path);

	if(!inputFile.fail())
	{
		while (!inputFile.eof())
		{
			int id;
			inputFile >> id;

			Map* temp = this->fullMapList->LoadMapFromID(fullMapList->GetTail(), id);

			//aggiornare mappa a seconda dei nemici e oggetti spawnati

			this->fullMapList->AddMap(temp);
		}
	}
	
	inputFile.close();
}

void MapManager::GenerateDrop(WINDOW * playwin, OggettoMappa* item[])
{
	this->currentMapList->GetTail()->GetItemDrop() -> newObject(chosenObject(item));

	int x = this->GetCurrentMapList()->GetTail()->GetSpawnItem().x;
    this->currentMapList->GetTail()->GetItemDrop() -> setXOgg(x);
    int y = this ->GetCurrentMapList()->GetTail()->GetSpawnItem().y;
	this->currentMapList->GetTail()->GetItemDrop() -> setYOgg(y);
}