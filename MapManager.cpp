#include "MapManager.h"

MapManager::MapManager(WINDOW* win)
{
    this->window = win;
    initializeFullMapList();
    this->currentMapList = new MapList();
}

void MapManager::initializeFullMapList()
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

			this->fullMapList->addMap(m1);
			this->fullMapList->addMap(m2);
		}
		//head = head->prec; //il ciclo while crea un livello vuoto in più in fondo
		//head = head->prec;
		//head->next = NULL;

		this->fullMapList->SetTail(this->fullMapList->GetTail()->GetPrev()); //il ciclo while crea un livello vuoto in più in fondo
		//this->fullMapList->SetTail(this->fullMapList->GetTail()->GetPrev());
		//this->fullMapList->GetTail()->SetNext(NULL);
	}

    this->numMaps = this->fullMapList->countMaps(fullMapList->GetTail());
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

void MapManager::generateNewMap()
{
    int levelToLoadID = rand() % numMaps;
	//int levelToLoadID = this->numMaps - 1; //debug
    //this->numMaps--;
    this->currentMapList->addMap(this->fullMapList->loadMapFromID(this->fullMapList->GetTail(), levelToLoadID));
	this->currentMapList->GetTail()->generateEnemies();
	this->currentMapList->GetTail()->generateItems();
}

void MapManager::drawCurrentMap()
{
	box(this->window, 0, 0);
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COLUMN; j++)
		{
			char character = ' ';
			if (this->currentMapList->GetTail()->GetMap()[i][j] == 0)
				character = ' ';
			else if (this->currentMapList->GetTail()->GetMap()[i][j] == 1)
				character = '_';
			else if (this->currentMapList->GetTail()->GetMap()[i][j] == 2)
				character = '|';
			else
				character = ' ';
			mvwprintw(this->window, i + 1, j + 1, "%c", character);
		}
	}
	
	for (int i = 0; i < this->currentMapList->GetTail()->GetNumPositionEnemies(); i++)
	{
		mvwprintw(this->window, this->currentMapList->GetTail()->GetPositionEnemies()[i].y, this->currentMapList->GetTail()->GetPositionEnemies()[i].x, 
					"%c", 'N');
	}
	
	for (int i = 0; i < this->currentMapList->GetTail()->GetNumPositionItems(); i++)
	{
		mvwprintw(this->window, this->currentMapList->GetTail()->GetPositionItems()[i].y, this->currentMapList->GetTail()->GetPositionItems()[i].x, 
					"%c", 'O');
	}
	
	//create_hero(win, 19, 2);

	wrefresh(this->window);
}

/*
Oltre alle informazioni relative ad ogni livello, salvare il numero di livelli caricati e statistiche del protagonista
*/

void MapManager::loadSavedMaps()
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

			Map* temp = this->fullMapList->loadMapFromID(fullMapList->GetTail(), id);

			//aggiornare mappa a seconda dei nemici e oggetti spawnati

			this->fullMapList->addMap(temp);
		}
	}
	
	inputFile.close();
}