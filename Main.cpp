#include "Market.h"
#define ROW 30
#define COLUMN 160
#define HEIGHT 9
#define WIDTH 16
int main(){
    initscr();
    noecho();
    cbreak();
    Hero h = new Hero();
    WINDOW* win = newwin(ROW, COLUMN, 0,0);
	box(win, 0, 0);
	refresh();
	wrefresh(win);
    keypad(win, true);
    Market m = Market();
    int choice, highlight = 0;
    bool cont = false;

    mvwprintw(win,1,32,"        |||         |||         |||         |||||||     |||      |||  ||||||||||  |||||||||||||");
    mvwprintw(win,2,32,"       |||||     |||||        || ||        |||   |||   |||     |||   |||              |||      ");
    mvwprintw(win,3,32,"      ||| ||  ||| |||       ||   ||       |||    |||  |||   |||     |||              |||       ");
    mvwprintw(win,4,32,"     |||  || ||  |||      ||     ||      |||   |||   ||| |||       |||              |||        ");
    mvwprintw(win,5,32,"    |||   |||   |||     ||       ||     ||||||      |||||         ||||||||||       |||         ");
    mvwprintw(win,6,32,"   |||         |||    |||||||||||||    |||  |||    ||| |||       |||              |||          ");
    mvwprintw(win,7,32,"  |||         |||   ||           ||   |||   |||   |||   |||     |||              |||           ");
    mvwprintw(win,8,32," |||         |||  ||             ||  |||    |||  |||     |||   |||              |||            ");
    mvwprintw(win,9,32,"|||         |||  ||              || |||     ||| |||      |||  ||||||||||       |||             ");

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
    //stampo caratteri nelle relative box
    mvwprintw(item1, 4, 7, (m.getItem(0)) -> getSkin());
    mvwprintw(item2, 4, 7, (m.getItem(1)) -> getSkin());
    mvwprintw(item3, 4, 7, (m.getItem(2)) -> getSkin());
    mvwprintw(item4, 4, 7, (m.getItem(3)) -> getSkin());
    mvwprintw(item5, 4, 7, (m.getItem(4)) -> getSkin());
    mvwprintw(item6, 1, 4, "CONTINUE");
    refresh();
    wrefresh(item1);
    wrefresh(item2);
    wrefresh(item3);
    wrefresh(item4);
    wrefresh(item5);
    wrefresh(item6);




    while(1){
    refresh();

        switch(highlight){
            case 0:
                mvwprintw(item1, 4, 6, "|");
                mvwprintw(item2, 4, 6, " ");
                break;
            case 1:
                mvwprintw(item2, 4, 6, "|");
                mvwprintw(item1, 4, 6, " ");
                mvwprintw(item3, 4, 6, " ");
                break;
            case 2:
                mvwprintw(item3, 4, 6, "|");
                mvwprintw(item2, 4, 6, " ");
                mvwprintw(item4, 4, 6, " ");
                break;
            case 3:
                mvwprintw(item4, 4, 6, "|");
                mvwprintw(item3, 4, 6, " ");
                mvwprintw(item5, 4, 6, " ");
                break;
            case 4:
                mvwprintw(item5, 4, 6, "|");
                mvwprintw(item4, 4, 6, " ");
                break;
            case 5: //continue
                mvwprintw(item6, 1, 3, "|");
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

        choice = wgetch(win);
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
                mvwprintw(item1, 4, 6, " ");
                mvwprintw(item2, 4, 6, " ");
                mvwprintw(item3, 4, 6, " ");
                mvwprintw(item4, 4, 6, " ");
                mvwprintw(item5, 4, 6, " ");
                break;
            case KEY_UP:
                if(cont){
                    cont = false;
                    highlight = 0;
                    mvwprintw(item6, 1, 3, " ");
                }
                break;
            default:
                break;
        }
        if(choice == 10 && cont)
        break;
        else if (choice == 10){
            string str2 = m.getItem(highlight)->purchase(h); //mettere l'eroe
            printw("%s", str2.c_str());
            wrefresh(win);
        }
    }
    return 0;
}