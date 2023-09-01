#include "ProgettoGame.h"

int main() 
{
	initscr();
	noecho();
	cbreak();
	curs_set(FALSE);

	create_menu(); //visualizzo il menù principale all'apertura del gioco

	//INSERIRE QUI LIVELLO MARKET
	
	//Inizializzazione finestra di gioco
	WINDOW* win = newwin(ROW + 2, COLUMN + 2, 2, 5);
	box(win, 0, 0);
	refresh();
	wrefresh(win);
	srand(time(NULL));
	keypad(win, true);

	//Inizializzazione prima mappa di gioco
	MapManager* mapManager = new MapManager(win);
	mapManager->GenerateNewMap();
	//mapManager->GetCurrentMapList()->PrintMaps(mapManager->GetCurrentMapList()->GetTail());

	//Inizializzazione eroe
	string n = "Ettore";
	Hero* player = new Hero(win, 19, 1, 7, mapManager, false, n);

	//Inizializzazione lista di nemici
	p_nodo h = NULL;
	srand((unsigned) time(NULL));
	h = generate_enemies(win, mapManager, 0);

	//Inizio del loop di gioco
	int gameState = 1;
	while (gameState > 0)
	{
		while (player->getHealth() > 0)
		{
			h = game_loop(win, mapManager, player, h);
			wtimeout(win, 100); //se l'utente non preme alcun tasto entro tot millisecondi, procede (IMPORTANTE!!!)
			flushinp();
			//gameState = 0;
		}
		napms(2000);
		perdita();
		napms(5000);
		player->setHealth(400);
		create_menu();
	}
	endwin();
	
	return 0;
}

p_nodo game_loop(WINDOW* win, MapManager* mapManager, Hero* player, p_nodo h){
	//visualzzo box statistiche
	creaFinestra();
	//salvo stato del giocatore su file (NOTA PER ME: salviamo il level o il diff_level? O, meglio, entrambi?)
	saveCharacterStats(player->player_name, player->getDefense(), player->getHealth(), player->getStrenght(), player->getMoney(), player->getLuck(), player->score, player->diff_level);
		
	//controllo se è avvenuto un game over
	/*if(player->getHealth()<=0){
		perdita();
	}*/

	int key = wgetch(win); //input da tastiera
	mapManager->DrawCurrentMap();

	//aggiornamento del livello di difficoltà se si ha raggiunto un certo score
	if(player->score >= player->score_threshold){
		(player->diff_level)++;
		(player->score_count) += (player->score_count)*0.05;
		player->score_threshold = player->score + player->score_count;
	}

	h = map_change(win, mapManager, player, h); //controlla se devo cambiare mappa (e, in tal caso, la cambia)

	//aggiornamento della posizione dei nemici
	display_list(h);
    h = action_list(win, h, player);

	player_skin_select(key, player); //selezione della giusta skin dell'eroe da visualizzare

	player->hit_direction = 0;

	return h;
}

void player_skin_select(int key, Hero* player){
	if(player->getHealth()>0){
		player->getmv(key);
		if(player->hit_direction!=0)
			player->display(player->player_shape_left_hit, player->player_shape_right_hit);
		else if(player->isAttackingDown){
			player->display(player->player_shape_attack_down, player->player_shape_attack_down);
		}
		else
		player->display(player->player_shape_left, player->player_shape_right);
	}
	else if(player->getHealth() <= 0){
        player->setHealth(0);
		player->display(player->player_shape_dead, player->player_shape_dead);
	}
}

p_nodo map_change(WINDOW* win, MapManager* mapManager, Hero* player, p_nodo h){
	//se il personaggio si trova nell'angolo in basso a dx della window e sta guardando a dx, passa alla mappa successiva
	if((player->yLoc == 19 && player->xLoc >= 153) && player->is_left == false){
		//carica livello successivo, se non esiste aggiungere un nuovo livello
		if (mapManager->GetCurrentMapList()->GetTail()->GetNext() != NULL){
			mapManager->GetCurrentMapList()->NextMap();
			mapManager->DrawCurrentMap();
		}
		else{
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
		h = generate_enemies(win, mapManager, player->diff_level);
	}
	//se il personaggio si trova nell'angolo in basso a sx della window e sta guardando a sx, passa alla mappa precedente (a meno che non sia nella prima mappa)
	else if(player->level!=1 && (player->yLoc == 19 && player->xLoc <= 1) && player->is_left == true){
		mapManager->GetCurrentMapList()->PreviousMap();
		mapManager->DrawCurrentMap();

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

	return h;
}