#include "mappa.h"

int main() 
{
	initscr();
	noecho();
	cbreak();
	
	WINDOW* win = newwin(22, 82, 0, 0);
	box(win, 0, 0);
	refresh();
	wrefresh(win);
	srand(time(NULL));
	keypad(win, true);
	
	punt_livello listaLivelli = inizializzaListaLivelli(NULL);
	if (listaLivelli != NULL)	//se i livelli sono stati caricati, procedere
	{
		disegnaMappa(win, listaLivelli);
		
		int gameState = 1; //start
		while (gameState > 0)
		{
			int key = wgetch(win);
			//Game Over: gameState = 0
			//gameState = 0;
			if (key == '0')
			{
				if (listaLivelli->next != NULL)
				{
					disegnaMappa(win, listaLivelli->next);
					listaLivelli = listaLivelli->next;
				}
				else
				{
					gameState = 0;
				}
			}
		}
	}
	endwin();
	
	return 0;
}
