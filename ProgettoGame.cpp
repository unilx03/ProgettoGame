#include "ProgettoGame.h"

int main() 
{
	//settings di ncurses
	initscr();
	noecho();
	cbreak();
	curs_set(FALSE);
	
	//Inizio del loop di gioco
	int gameState = 1;
	bool sale = false;
	while (gameState > 0 )
	{
		//Inizializzazione finestra di gioco
		WINDOW* win = newwin(ROW + 2, COLUMN + 2, 2, 5);
		box(win, 0, 0);
		refresh();
		wrefresh(win);
		srand(time(NULL));
		keypad(win, true);

		//Inizializzazione prima mappa di gioco 
		MapManager* mapManager = new MapManager(win);
		mapManager->GenerateNewMap(true);

		int menu_choice = create_menu(); //visualizzo il menù principale all'apertura del gioco
		if(menu_choice == 0)
			gameState = 0;
		erase(); //cancella tutto ciò che c'è sullo schermo
	
		if(gameState > 0){

			string n = "Ettore";
			Hero* player = new Hero(win, 19, 1, 7, mapManager, false, n);

			//L'utente ha scelto di fare una nuova partita
			if(menu_choice == 1){
				player->player_name = inseriscinome();
				erase();
			}
			//L'utente ha scelto di continuare una partita già salvata
			else if(menu_choice == 2){
				//Carico gli ultimi dati di salvataggio da file
				player->player_name = selezionenome();
				int player_data[10];
				vettoredati(player_data);
				player->setDefense(player_data[2]);
				player->setMaxHp(player_data[9]);
				player->setStrenght(player_data[3]);
				player->setMoney(player_data[1]);
				player->setLuck(player_data[4]);
				player->score = 0;
				player->diff_level = player_data[7];
				player->setSale(player_data[8]);
				if((player->getSale())==1){ //Sconti nel market
					sale = true;
					player_data[8] = 0;
				}
			}

			//Inizializzazione lista di nemici
			p_nodo h = NULL;
			srand((unsigned) time(NULL));
			h = generate_enemies(win, mapManager, player->diff_level);
			p_en_list list = NULL;
			list = tail_insert(list, h);
			
			create_market(player, sale); //visualizzo il market
			//Resetto ciò che riguarda gli sconti
			player->setSale(0);
			sale = false;

			erase(); //cancella tutto ciò che c'è sullo schermo

			box(win, 0, 0);
			refresh();	//Importante!!
			wrefresh(win); //Importante!!
			char message[] = "Press any key to start!";
			mvwprintw(win, 11, 70, message);

			while (player->getHealth() > 0)
			{	
				//visualzzo box statistiche
				creaFinestra();
				//salvo stato del giocatore su file
				saveCharacterStats(player->player_name, player->getDefense(), player->getHealth(), player->getStrenght(), player->getMoney(), player->getLuck(), player->score, player->level, player->diff_level, player->getSale(), player->getMaxHp());
				creaFinestra();	

				h = game_loop(win, mapManager, player, h, list);

				wtimeout(win, 100); //se l'utente non preme alcun tasto entro tot millisecondi, procede (IMPORTANTE!!!)
				flushinp();
			}
			napms(2000);
			creaFinestra();
			perdita();
			napms(3000);
			
			player->setHealth(player->getMaxHp());

			p_en_list list2 = list;
			delete list2;
			list = NULL;

			MapManager* map2 = mapManager;
			delete map2;
			mapManager = NULL;
		}
	}

	endwin();
	
	return 0;
}

p_nodo game_loop(WINDOW* win, MapManager* mapManager, Hero* player, p_nodo h, p_en_list list){

	int key = wgetch(win); //input da tastiera

	mapManager->DrawCurrentMap();
	player->hero_object_collision(mapManager->GetCurrentMapList()->GetTail()->GetItemDrop());
	//stampa a schermo dell'effetto dell'oggetto appena raccolto
	if(player->mapManager->GetCurrentMapList()->GetTail()->GetItemPicked()){
		mvwprintw(win, 1, 1, "Object boost:");
		mvwprintw(win, 1, 15, mapManager->GetCurrentMapList()->GetTail()->GetItemDrop()->getStatAffected());
	}
	//aggiornamento del livello di difficoltà se si ha raggiunto un certo score
	if(player->score >= player->score_threshold){
		(player->diff_level)++;
		(player->score_count) += (player->score_count)*0.05;
		player->score_threshold = player->score + player->score_count;
	}
	h = map_change(win, mapManager, player, list); //controlla se devo cambiare mappa (e, in tal caso, la cambia)

	//aggiornamento della posizione dei nemici
	
	display_list(h);
    h = action_list(win, h, player);
	search_enemies(list, player->level)->list = h;

	player_skin_select(key, player); //selezione della giusta skin dell'eroe da visualizzare

	player->hit_direction = 0;
	player->has_found_obj = false;

	//salvo stato del giocatore su file
	saveCharacterStats(player->player_name, player->getDefense(), player->getHealth(), player->getStrenght(), player->getMoney(), player->getLuck(), player->score, player->level, player->diff_level, player -> getSale(), player->getMaxHp());
	//visualzzo box statistiche
	creaFinestra();	

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
		else if(player->isAttackingDown){
			player->display(player->player_shape_attack_down, player->player_shape_attack_down);
		}
		else if(player->has_found_obj){
			player->display(player->player_shape_left_obj, player->player_shape_right_obj);
		}
		else
		player->display(player->player_shape_left, player->player_shape_right);
	}
	else if(player->getHealth() <= 0){
        player->setHealth(0);
		player->display(player->player_shape_dead, player->player_shape_dead);
	}
}

p_nodo map_change(WINDOW* win, MapManager* mapManager, Hero* player, p_en_list list){
	p_nodo h = NULL;
	h = (search_enemies(list, player->level))->list;
	
	//se il personaggio si trova nell'angolo in basso a dx della window e sta guardando a dx, passa alla mappa successiva
	if((player->yLoc == 19 && player->xLoc >= 153) && player->is_left == false){
		//tolgo gli effetti degli oggetti temporanei
		player -> setInvincibility(false);
		player -> setDoubleMoney(false);
		player ->setDoubleScore(false);

		player->yLoc = 19;
		player->xLoc = 1;
		player->is_left = false;
		(player->level)++;

		//elimino la lista di proiettili
		Hero::p_bullet b = player->h;
		delete b;
		player->h = NULL;

		//carica livello successivo, se non esiste aggiungere un nuovo livello
		if (mapManager->GetCurrentMapList()->GetTail()->GetNext() != NULL){
			mapManager->GetCurrentMapList()->NextMap();
			mapManager->DrawCurrentMap();

			h = search_enemies(list, player->level)->list;
		}
		else{
			if(player -> getLuck()>0){
				mapManager->GenerateNewMap(true); //ho ancora punti fortuna da utilizzare
				player -> setLuck((player -> getLuck())-1); //rimuovo il punto fortuna utilizzato
			}
			else
				mapManager->GenerateNewMap(false); //non ho più punti fortuna da utilizzare
			mapManager->DrawCurrentMap();

			h = generate_enemies(win, mapManager, player->diff_level);
			list = tail_insert(list, h);
		}
	}
	//se il personaggio si trova nell'angolo in basso a sx della window e sta guardando a sx, passa alla mappa precedente (a meno che non sia nella prima mappa)
	else if(player->level!=1 && (player->yLoc == 19 && player->xLoc <= 1) && player->is_left == true){
		player->yLoc = 19;
		player->xLoc = 153;
		player->is_left = true;
		(player->level)--;

		//elimino la lista di proiettili
		Hero::p_bullet b = player->h;
		delete b;
		player->h = NULL;
		
		mapManager->GetCurrentMapList()->PreviousMap();
		mapManager->DrawCurrentMap();

		h = search_enemies(list, player->level)->list;
	}
	return h;
}

void create_market(Hero* player, bool sale){

	WINDOW* win = newwin(ROWMARKET, COLUMN, 0,0);
	box(win, 0, 0);
	refresh();
	wrefresh(win);
	srand(time(NULL));
	keypad(win, true);
	int choice, highlight = 0;
    bool cont = false;

	//Inizializzazione array oggetti market
	OggettoMarket * item[N];
	item[0] = new OggettoMarket ("BISCOTTO VITA","<3", 0.2,"Health",70);
    item[1] = new OggettoMarket("SPINACI", "YY", 0.35,"Strenght",40);
    item[2] = new OggettoMarket("POZIONE SALTO", "()", 1,"JumpForce",150);
    item[3] = new OggettoMarket("SCUDO CAROTA", "][", 1,"Defense",90);
    item[4] = new OggettoMarket("CAROTA FORTUNA", "X>", 1,"Luck",120);
	if(sale){ //Gli sconti dimezzano il prezzo di ogni oggetto del market
		item[0]->setPrice(item[0]->getPrice()/2);
		item[1]->setPrice(item[1]->getPrice()/2);
		item[2]->setPrice(item[2]->getPrice()/2);
		item[3]->setPrice(item[3]->getPrice()/2);
		item[4]->setPrice(item[4]->getPrice()/2);
	}
	else{
		item[0]->setPrice(70);
		item[1]->setPrice(40);
		item[2]->setPrice(150);
		item[3]->setPrice(90);
		item[4]->setPrice(120);
	}
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
    creaFinestra();
    saveCharacterStats(player->player_name, player->getDefense(), player->getHealth(), player->getStrenght(), player->getMoney(), player->getLuck(), player->score, player->level, player->diff_level, player -> getSale(), player->getMaxHp());
	creaFinestra();	

	while(1){
        refresh();

        //stampa evidenziazione
        printHighlight(item1, item2, item3, item4, item5, item6, highlight);

        choice = wgetch(win);
        
        //cambia evidenziazione
        changeHighlight(choice, highlight, cont);
        
        //controlla la scelta e agisce di conseguenza
        //se la funzione ritorna true significa che è stata premuta Y
        if(checkChoice(choice, highlight, cont, win, item1, item2, item3, item4, item5, item6, item, player)){
            break;
		}
		
		saveCharacterStats(player->player_name, player->getDefense(), player->getHealth(), player->getStrenght(), player->getMoney(), player->getLuck(), player->score, player->level, player->diff_level, player -> getSale(), player->getMaxHp());
		creaFinestra();
        
    }

}