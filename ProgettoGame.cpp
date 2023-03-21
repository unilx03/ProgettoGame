#include "mappa.h"

int main() 
{
	initscr();
	noecho();
	cbreak();
	
	WINDOW* win = newwin(22, 82, 2, 5);
	box(win, 0, 0);
	refresh();
	wrefresh(win);
	srand(time(0));
	keypad(win, true);
	
	punt_livello listaLivelli = inizializzaListaLivelli(NULL); //tutte le mappe del gioco, si scorrere andando indietro
	int livelliTotali = contaLivelli(listaLivelli);
	punt_livello livelliCorrenti = NULL; //mappe caricate nella partita corrente, si scorre andando indietro
	
	//stampaLivelli(listaLivelli);
	
	if (listaLivelli != NULL)	//se i livelli sono stati caricati, procedere
	{
		int idLivelloDaCaricare = rand() % livelliTotali;
		livelliCorrenti = aggiungiLivelloDopo(livelliCorrenti, caricaMappaDaID(listaLivelli, idLivelloDaCaricare));
		disegnaMappa(win, livelliCorrenti);
		//disegnaMappa(win, listaLivelli);
		
		int gameState = 1; //start
		while (gameState > 0)
		{
			int key = wgetch(win);
			//Game Over: gameState = 0
			//gameState = 0;
			if (key == 'a') //carica livello precedente, se non esiste mantiene livello corrente
			{
				livelliCorrenti = livelloPrecedente(livelliCorrenti);
				disegnaMappa(win, livelliCorrenti);
				/*if (listaLivelli->prec != NULL)
				{
					disegnaMappa(win, listaLivelli->prec);
					listaLivelli = listaLivelli->prec;
				}
				else
				{
					gameState = 0;
				}*/
			}
			else if (key == 'd') //carica livello successivo, se non esiste aggiungere un nuovo livello
			{
				if (livelloSuccessivo(livelliCorrenti) != NULL)
				{
					livelliCorrenti = livelloSuccessivo(livelliCorrenti);
					disegnaMappa(win, livelliCorrenti);
				}
				else
				{
					idLivelloDaCaricare = rand() % livelliTotali;
					livelliCorrenti = aggiungiLivelloDopo(livelliCorrenti, caricaMappaDaID(listaLivelli, idLivelloDaCaricare));
					disegnaMappa(win, livelliCorrenti);
				}
			}
		}
	}
	endwin();
	
	return 0;
}
