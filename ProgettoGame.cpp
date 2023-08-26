
//#include "Entities/Character.h"
//#include "Entities/Hero.h"
//#include "Entities/SetEnemiesList.h"
//#include "Entities/Enemy.h"
//#include "Entities/BossEnemy.h"

//#include "oggetto.h"
#include "MarketScreen.h"
int main() 
{
	initscr();
	noecho();
	cbreak();
	curs_set(FALSE);
	
	WINDOW* win = newwin(ROW, COLUMN, 0,0);
	box(win, 0, 0);
	refresh();
	wrefresh(win);
	srand(time(NULL));
	keypad(win, true);
	int choice, highlight = 0;
    bool cont = false;

	//Inizializzazione array oggetti market
	OggettoMarket * item[N];
	item[0] = new OggettoMarket ("BISCOTTO VITA","<3", 0.05,"health",55);
    item[1] = new OggettoMarket("SPINACI", "YY", 0.03,"strenght",44);
    item[2] = new OggettoMarket("POZIONE SALTO", "()", 0.02,"JumpForce",22);
    item[3] = new OggettoMarket("SCUDO CAROTA", "][", 0.05,"defense",11);
    item[4] = new OggettoMarket("CAROTA FORTUNA", "X>", 0.01,"luck",100);

	//inizializzazione MapManager, Hero e Market
    MapManager* mapManager = new MapManager(win);
    char n[] = "Ettore";
	Hero* h = new Hero(win, 19, 0, 7, mapManager, false, n);
    h -> setMoney(100);

	//Inizializzazione finestre item + continue
    WINDOW* item1 = newwin(HEIGHT, WIDTH, 16, 2);
    WINDOW* item2 = newwin(HEIGHT, WIDTH, 16, 37);
    WINDOW* item3 = newwin(HEIGHT, WIDTH, 16, 72);
    WINDOW* item4 = newwin(HEIGHT, WIDTH, 16, 107);
    WINDOW* item5 = newwin(HEIGHT, WIDTH, 16, 142);
    WINDOW* item6 = newwin(3, WIDTH, 26, 142);
    box(item1, 0, 0);
    box(item2, 0, 0);
    box(item3, 0, 0);
    box(item4, 0, 0);
    box(item5, 0, 0);
    box(item6, 0, 0);

	//stampa schermo
    printScreen(win, item1, item2, item3, item4, item5, item6, item);

	while(1){
        refresh();

        //stampa evidenziazione
        printHighlight(item1, item2, item3, item4, item5, item6, highlight);

	int gameState = 1; //start
	while (gameState > 0)
	{
		//visualzzo box statistiche
		creaFinestra();
		//salvo stato del giocatore su file
		saveCharacterStats(n, player->getDefense(), player->getHealth(), player->getStrenght(), player->getMoney(), player->getLuck(), player->score, player->level);

		int key = wgetch(win);

		//Game Over: gameState = 0
		//gameState = 0;

		//wclear(win);
		mapManager->DrawCurrentMap();

		/*if (key == 'a') //carica livello precedente, se non esiste mantiene livello corrente
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
		}*/

		//se il personaggio si trova nell'angolo in basso a dx della window e sta guardando a dx, passa alla mappa successiva
		if((player->yLoc == 19 && player->xLoc == 153) && player->is_left == false){
			//carica livello successivo, se non esiste aggiungere un nuovo livello
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

			player->yLoc = 19;
			player->xLoc = 1;
			player->is_left = false;
			(player->level)++;

			//(BRUNI) SALVARE SU FILE LISTA NEMICI ASSOCIATA A MAPPA!
			//eliminare lista nemici corrente e generarne un'altra (altrimenti (BRUNI) CARICARE DA FILE QUELLA DELLA MAPPA SUCCESSIVA, SE ESISTE GIA'!)
			
			//le seguenti righe gestiscono il caso in cui nel file non sia già stata salvata la lista di nemici associata alla mappa successiva
			p_nodo h2 = h;
			delete h2;
			h = NULL;
			h = generate_enemies(3, win, mapManager);
		}
		//se il personaggio si trova nell'angolo in basso a sx della window e sta guardando a sx, passa alla mappa precedente
		else if((player->yLoc == 19 && player->xLoc == 1) && player->is_left == true){
			mapManager->GetCurrentMapList()->PreviousMap();
			mapManager->DrawCurrentMap();

			//NOTA: bug nel primo livello; se vado in basso a sx, l'eroe viene spawnato a dx
			player->yLoc = 19;
			player->xLoc = 153;
			player->is_left = true;
			(player->level)--;

			//(BRUNI) SALVARE SU FILE LISTA NEMICI ASSOCIATA A MAPPA!
			p_nodo h2 = h;
			delete h2;
			h = NULL;
			//(BRUNI) CARICARE DA FILE QUELLA DELLA MAPPA PRECEDENTE!
		}

		display_list(h);
        h = action_list(win, h, player);

		if(player->getHealth()>0){ //NOTA: if ed else if provvisori. Giusto per capire quando avviene un gameover.
			player->getmv(key);
			if(player->hit_direction!=0)
				player->display(player->player_shape_left_hit, player->player_shape_right_hit);
			else
				player->display(player->player_shape_left, player->player_shape_right);
		}
		else if(player->getHealth() == 0){
			player->setHealth(-1);
			player->display(player->player_shape_dead, player->player_shape_dead);
		}

		player->hit_direction = 0;

		wtimeout(win, 150); //se l'utente non preme alcun tasto entro tot millisecondi, procede (IMPORTANTE!!!)

		flushinp();

		//gameState = 0;
	}
        choice = wgetch(win);
        
        //cambia evidenziazione
        changeHighlight(choice, highlight, cont);
        
        //controlla la scelta e agisce di conseguenza
        //se la funzione ritorna true significa che è stata premuta Y
        if(checkChoice(choice, highlight, cont, win, item1, item2, item3, item4, item5, item6, item, h))
            break;
    }
	endwin();
	
	return 0;
}