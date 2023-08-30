
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