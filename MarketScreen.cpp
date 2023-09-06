#include "MarketScreen.h"

void printScreen(WINDOW* win, WINDOW* item1, WINDOW* item2, WINDOW* item3, WINDOW* item4, WINDOW* item5, WINDOW* item6, OggettoMarket* m[]){
    WINDOW* message = newwin((HEIGHT/2)+1, WIDTH*2, 10, 64);
    wrefresh(message);
    //Print scritta
    mvwprintw(win,1,32,"        |||         |||         |||         |||||||     |||      |||  ||||||||||  |||||||||||||");
    mvwprintw(win,2,32,"       |||||     |||||        || ||        |||   |||   |||     |||   |||              |||      ");
    mvwprintw(win,3,32,"      ||| ||  ||| |||       ||   ||       |||    |||  |||   |||     |||              |||       ");
    mvwprintw(win,4,32,"     |||  || ||  |||      ||     ||      |||   |||   ||| |||       |||              |||        ");
    mvwprintw(win,5,32,"    |||   |||   |||     ||       ||     ||||||      |||||         ||||||||||       |||         ");
    mvwprintw(win,6,32,"   |||         |||    |||||||||||||    |||  |||    ||| |||       |||              |||          ");
    mvwprintw(win,7,32,"  |||         |||   ||           ||   |||   |||   |||   |||     |||              |||           ");
    mvwprintw(win,8,32," |||         |||  ||             ||  |||    |||  |||     |||   |||              |||            ");
    mvwprintw(win,9,32,"|||         |||  ||              || |||     ||| |||      |||  ||||||||||       |||             ");

    //FINESTRA 1
    mvwprintw(item1, 1, 1, "BISCOTTO  VITA");
    mvwprintw(item1, 2, 1, "--------------");
    mvwprintw(item1, 4, 7, m[0] -> getSkin());
    mvwprintw(item1, 6, 1, "______________");
    mvwprintw(item1, 7, 7, "%d", m[0] -> getPrice());

    //FINESTRA 2
    mvwprintw(item2, 1, 4, "SPINACIO");
    mvwprintw(item2, 2, 1, "--------------");
    mvwprintw(item2, 4, 7, m[1] -> getSkin());
    mvwprintw(item2, 6, 1, "______________");
    mvwprintw(item2, 7, 7, "%d", m[1] -> getPrice());

    //FINESTRA 3
    mvwprintw(item3, 1, 1, "POZIONE  SALTO");
    mvwprintw(item3, 2, 1, "--------------");
    mvwprintw(item3, 4, 7, m[2] -> getSkin());
    mvwprintw(item3, 6, 1, "______________");
    mvwprintw(item3, 7, 7, "%d", m[2] -> getPrice());

    //FINESTRA 4
    mvwprintw(item4, 1, 2, "SCUDO CAROTA");
    mvwprintw(item4, 2, 1, "--------------");
    mvwprintw(item4, 4, 7, m[3] -> getSkin());
    mvwprintw(item4, 6, 1, "______________");
    mvwprintw(item4, 7, 7, "%d", m[3] -> getPrice());

    //FINESTRA 5
    mvwprintw(item5, 1, 1, "CAROTA FORTUNA");
    mvwprintw(item5, 2, 1, "--------------");
    mvwprintw(item5, 4, 7, m[4] -> getSkin());
    mvwprintw(item5, 6, 1, "______________");
    mvwprintw(item5, 7, 7, "%d", m[4] -> getPrice());

    mvwprintw(item6, 1, 4, "CONTINUE");
    refresh();
    wrefresh(item1);
    wrefresh(item2);
    wrefresh(item3);
    wrefresh(item4);
    wrefresh(item5);
    wrefresh(item6);
}

void printHighlight(WINDOW* item1, WINDOW* item2, WINDOW* item3, WINDOW* item4, WINDOW* item5, WINDOW* item6, int highlight){
    switch(highlight){
            case 0:
                wattron(item1, A_REVERSE);
                mvwprintw(item1, 1, 1, "BISCOTTO  VITA");
                wattroff(item1, A_REVERSE);
                mvwprintw(item2, 1, 4, "SPINACIO");
                mvwprintw(item6, 1, 4, "CONTINUE");
                break;
            case 1:
                wattron(item2, A_REVERSE);
                mvwprintw(item2, 1, 4, "SPINACIO");
                wattroff(item2, A_REVERSE);
                mvwprintw(item1, 1, 1, "BISCOTTO  VITA");
                mvwprintw(item3, 1, 1, "POZIONE  SALTO");
                break;
            case 2:
                wattron(item3, A_REVERSE);
                mvwprintw(item3, 1, 1, "POZIONE  SALTO");
                wattroff(item3, A_REVERSE);
                mvwprintw(item2, 1, 4, "SPINACIO");
                mvwprintw(item4, 1, 2, "SCUDO CAROTA");
                break;
            case 3:
                wattron(item4, A_REVERSE);
                mvwprintw(item4, 1, 2, "SCUDO CAROTA");
                wattroff(item4, A_REVERSE);
                mvwprintw(item3, 1, 1, "POZIONE  SALTO");
                mvwprintw(item5, 1, 1, "CAROTA FORTUNA");
                break;
            case 4:
                wattron(item5, A_REVERSE);
                mvwprintw(item5, 1, 1, "CAROTA FORTUNA");
                wattroff(item5, A_REVERSE);
                mvwprintw(item4, 1, 2, "SCUDO CAROTA");
                
                break;
            case 5: //continue
                wattron(item6, A_REVERSE);
                mvwprintw(item6, 1, 4, "CONTINUE");
                wattroff(item6, A_REVERSE);
                mvwprintw(item1, 1, 1, "BISCOTTO  VITA");
                mvwprintw(item2, 1, 4, "SPINACIO");
                mvwprintw(item3, 1, 1, "POZIONE  SALTO");
                mvwprintw(item4, 1, 2, "SCUDO CAROTA");
                mvwprintw(item5, 1, 1, "CAROTA FORTUNA");
                break;
            default:
                break;
        }
        wrefresh(item1);
        wrefresh(item2);
        wrefresh(item3);
        wrefresh(item4);
        wrefresh(item5);
        wrefresh(item6);
}

void changeHighlight(int choice, int & highlight, bool & cont){
    switch(choice){
            case KEY_LEFT:
                highlight--;
                if(highlight == -1)
                    highlight = 0;
                break;
            case KEY_RIGHT:
                highlight++;
                if(highlight == N)
                    highlight = N - 1;
                break;
            case KEY_DOWN:
                highlight = 5;
                cont = true;
                break;
            case KEY_UP:
                if(cont){
                    cont = false;
                    highlight = 0;
                }
                break;
            default:
                break;
    }
}

bool checkChoice(int choice, int highlight, bool cont, WINDOW* win, WINDOW* item1, WINDOW* item2, WINDOW* item3, WINDOW* item4, WINDOW* item5, WINDOW* item6, OggettoMarket* m[], Hero * h){
    if(choice == 10 && cont){
        WINDOW* message = newwin((HEIGHT/2)+1, WIDTH*2, 10, 64);
        box(message, 0, 0);
        mvwprintw(message, 2, 2, "DO YOU WANT TO CONTINUE? Y/N");
        wrefresh(message);
        choice = wgetch(win);
        if (choice == 89 || choice == 121) //controlla la lettera Y/y
            return true;
    }
    else if (choice == 10){
        string str2 = h->purchase(*(m[highlight])); //mettere l'eroe
        WINDOW* message = newwin((HEIGHT/2)+1, WIDTH*2, 10, 64);
        box(message, 0, 0);
        mvwprintw(message, 2, 6, str2.c_str());
        wrefresh(message);
        napms(500);
    }
    printScreen(win, item1, item2, item3, item4, item5, item6, m);
    return false;
}