#include "MarketScreen.h"

int main(){
    //inizializzazione variabili e finestra base
    initscr();
    noecho();
    cbreak();
    curs_set(FALSE);
    int choice, highlight = 0;
    bool cont = false;
    WINDOW* win = newwin(ROW, COLUMN, 0,0);
	box(win, 0, 0);

    //inizializzazione MapManager, Hero e Market
    MapManager* mapManager = new MapManager(win);
    char n[] = "Ettore";
	Hero* h = new Hero(win, 19, 0, 7, mapManager, false, n);
    h -> setMoney(100);
	refresh();
	wrefresh(win);
    keypad(win, true);
    Market m = Market();


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
    printScreen(win, item1, item2, item3, item4, item5, item6, m);
    
    while(1){
        refresh();

        //stampa evidenziazione
        printHighlight(item1, item2, item3, item4, item5, item6, highlight);

        choice = wgetch(win);
        
        //cambia evidenziazione
        changeHighlight(choice, highlight, cont);
        
        //controlla la scelta e agisce di conseguenza
        //se la funzione ritorna true significa che è stata premuta Y
        if(checkChoice(choice, highlight, cont, win, item1, item2, item3, item4, item5, item6, m, h))
            break;
    }
    endwin();
    return 0;
}