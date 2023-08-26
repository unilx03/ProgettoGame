#include "SetEnemiesList.h"
#include "FinestraP.h"
#include <string>

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

	string n = "Ettore";
	Hero* player = new Hero(win, 19, 0, 7, mapManager, false, n);

	//NOTA: bisognerà creare una lista di nemici per ogni mappa
	p_nodo h = NULL;
	srand((unsigned) time(NULL));
	h = generate_enemies(3, win, mapManager);

    /*h = head_insert(h, win, 10, 150, mapManager, 0);
	h = head_insert(h, win, 10, 140, mapManager, 1);
	h = head_insert(h, win, 3, 150, mapManager, 2);
	h = head_insert(h, win, 8, 60, mapManager, 3);
	h = head_insert(h, win, 17, 10, mapManager, 4);*/

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
	endwin();
	//cout << "For now executed" << endl;
	
	return 0;
}