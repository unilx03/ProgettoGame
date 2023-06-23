#include "MapManager.h"

//#include "Entities/Character.h"
//#include "Entities/Hero.h"
//#include "Entities/SetEnemiesList.h"
//#include "Entities/Enemy.h"
//#include "Entities/BossEnemy.h"

//#include "oggetto.h"

int main() 
{
	initscr();
	noecho();
	cbreak();
	curs_set(FALSE);
	
	WINDOW* win = newwin(ROW + 2, COLUMN + 2, 2, 5);
	box(win, 0, 0);
	refresh();
	wrefresh(win);
	srand(time(NULL));
	keypad(win, true);

	//mvwprintw(win, 10, 10, "*");

	MapManager* mapManager = new MapManager(win);
	//MapManager* mapManager = new MapManager(newwin(ROW + 2, COLUMN + 2, 2, 5));
	mapManager->generateNewMap();

	//mapManager->GetFullMapList()->printMaps(mapManager->GetFullMapList()->GetTail());
	//mapManager->GetCurrentMapList()->printMaps(mapManager->GetCurrentMapList()->GetTail());

	int gameState = 1; //start
	while (gameState > 0)
	{
		int key = wgetch(win);
		//Game Over: gameState = 0
		//gameState = 0;
		
		//wclear(win);
		mapManager->drawCurrentMap();

		if (key == 'a') //carica livello precedente, se non esiste mantiene livello corrente
		{
			mapManager->GetCurrentMapList()->previousMap();
			mapManager->drawCurrentMap();
		}
		else if (key == 'd') //carica livello successivo, se non esiste aggiungere un nuovo livello
		{
			if (mapManager->GetCurrentMapList()->GetTail()->GetNext() != NULL)
			{
				mapManager->GetCurrentMapList()->nextMap();
				mapManager->drawCurrentMap();
			}
			else
			{
				mapManager->generateNewMap();
				mapManager->drawCurrentMap();
			}
		}

		//gameState = 0;
	}
	endwin();
	//cout << "For now executed" << endl;
	
	return 0;
}
