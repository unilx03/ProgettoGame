#include "mappa.h"

int main() 
{
	initscr();
	noecho();
	cbreak();
	
	WINDOW* win = newwin(ROW + 2, COLUMN + 2, 2, 5);
	box(win, 0, 0);
	refresh();
	wrefresh(win);
	srand(time(NULL));
	keypad(win, true);
	
	punt_livello listaLivelli = inizializzaListaLivelli(NULL); //tutte le mappe del gioco, si scorrere andando indietro
	int livelliTotali = contaLivelli(listaLivelli);
	punt_livello livelliCorrenti = NULL; //mappe caricate nella partita corrente, si scorre andando indietro
	
	if (listaLivelli != NULL)	//se i livelli sono stati caricati, procedere
	{
		int idLivelloDaCaricare = rand() % livelliTotali;
		livelliCorrenti = aggiungiLivelloDopo(livelliCorrenti, caricaMappaDaID(listaLivelli, idLivelloDaCaricare));
		livelliCorrenti = generaNemici(livelliCorrenti);
		livelliCorrenti = generaOggetti(livelliCorrenti);
		disegnaMappa(win, livelliCorrenti);
		
		int gameState = 1; //start
		while (gameState > 0)
		{
			int key = wgetch(win);
			//Game Over: gameState = 0
			//gameState = 0;
			if (key == 'a') //carica livello precedente, se non esiste mantiene livello corrente
			{
				livello temp = livelliCorrenti;
				livelliCorrenti = livelloPrecedente(livelliCorrenti);
				if (temp != livelliCorrenti)
				{
					disegnaMappa(win, livelliCorrenti);
				}
				else //non sipuò tornare più indietro del primo livello
				{
					
				}
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
					livelliCorrenti = generaNemici(livelliCorrenti);
					livelliCorrenti = generaOggetti(livelliCorrenti);
					disegnaMappa(win, livelliCorrenti);
				}
			}
		}
	}
	endwin();
	
	return 0;
}
