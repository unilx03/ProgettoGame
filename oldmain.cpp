/*
#include "map.h"

//#include "Entities/Character.h"
#include "Entities/Hero.h"
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
	
	punt_level levelList = initializeLevelList(NULL); //tutte le mappe del gioco, si scorrere andando indietro
	int numLevels = countLevels(levelList);
	punt_level currentLevel = NULL; //mappe caricate nella partita corrente, si scorre andando indietro
	//printLevels(levelList);

	if (levelList != NULL)	//se i livelli sono stati caricati, procedere
	{
		//controllo se è partita nuova

		//int levelToLoadID = rand() % numLevels;
		int levelToLoadID = numLevels - 1;
		currentLevel = addLevel(currentLevel, loadMapFromID(levelList, levelToLoadID));
		currentLevel = generateEnemies(currentLevel);
		currentLevel = generateItems(currentLevel);
		drawMap(win, currentLevel);

		create_hero(win, 19, 2);   
		
		int gameState = 1; //start
		while (gameState > 0)
		{
			int key = wgetch(win);
			//Game Over: gameState = 0
			//gameState = 0;
			
			wclear(win);
			drawMap(win, currentLevel);

			if (key == 'a') //carica livello precedente, se non esiste mantiene livello corrente
			{
				level* temp = currentLevel;
				currentLevel = previousLevel(currentLevel);
				if (temp != currentLevel)
				{
					drawMap(win, currentLevel);
				}
				else //non si può tornare più indietro del primo livello
				{
					
				}
			}
			else if (key == 'd') //carica livello successivo, se non esiste aggiungere un nuovo livello
			{
				if (nextLevel(currentLevel) != NULL)
				{
					currentLevel = nextLevel(currentLevel);
					drawMap(win, currentLevel);
				}
				else
				{
					//levelToLoadID = rand() % numLevels;
					levelToLoadID--;
					currentLevel = addLevel(currentLevel, loadMapFromID(levelList, levelToLoadID));
					currentLevel = generateEnemies(currentLevel);
					currentLevel = generateItems(currentLevel);
					drawMap(win, currentLevel);
				}
			}
		}
	}
	endwin();
	
	
	return 0;
}
*/