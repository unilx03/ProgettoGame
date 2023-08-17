#include "SetEnemiesList.h"

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

	MapManager* mapManager = new MapManager(win);
	//MapManager* mapManager = new MapManager(newwin(ROW + 2, COLUMN + 2, 2, 5));
	mapManager->GenerateNewMap();
	//mapManager->GetCurrentMapList()->PrintMaps(mapManager->GetCurrentMapList()->GetTail());

	Hero* player = new Hero(win, 19, 2, 7, mapManager, "Ettore");
	p_nodo h = NULL;
    h = head_insert(h, win, 19, 150, mapManager, 2);
	 
	/*
	p_nodo h = NULL;
    h = head_insert(h, win, mapManager->GetCurrentMapList()->GetTail()->GetPositionEnemies()[0].y,
					mapManager->GetCurrentMapList()->GetTail()->GetPositionEnemies()[0].x, mapManager, 0);
    //h = head_insert(h, win, 17, 35, 2);
    //h = head_insert(h, win, 10, 20, 3);
    //h = head_insert(h, win, 10, 25, 4);*/

	/*char key = ' ';
	do
	{
		cin >> key;
		if (key != 'o' && key != ' ')
		{
			mapManager->GetCurrentMapList()->PrintMaps(mapManager->GetCurrentMapList()->GetTail());
			player->getmv(key);
			key = ' ';
		}
	}
	while (key != 'o');*/

	//mapManager->GetFullMapList()->printMaps(mapManager->GetFullMapList()->GetTail());
	//mapManager->GetCurrentMapList()->printMaps(mapManager->GetCurrentMapList()->GetTail());

	int gameState = 1; //start
	while (gameState > 0)
	{
		int key = wgetch(win);

		//Game Over: gameState = 0
		//gameState = 0;

		//wclear(win);
		mapManager->DrawCurrentMap();

		if (key == 'a') //carica livello precedente, se non esiste mantiene livello corrente
		{
			mapManager->GetCurrentMapList()->PreviousMap();
			mapManager->DrawCurrentMap();
		}
		else if (key == 'd') //carica livello successivo, se non esiste aggiungere un nuovo livello
		{
			if (mapManager->GetCurrentMapList()->GetTail()->GetNext() != NULL)
			{
				mapManager->GetCurrentMapList()->NextMap();
				mapManager->DrawCurrentMap();
			}
			else
			{
				mapManager->GenerateNewMap();
				mapManager->DrawCurrentMap();
			}
		}

		display_list(h);
        action_list(win, h);

		player->getmv(key);
		player->display(player->player_shape_left, player->player_shape_right);

		flushinp();

		//gameState = 0;
	}
	endwin();
	//cout << "For now executed" << endl;
	
	return 0;
}
