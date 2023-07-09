#include "Market.h"
#define ROW 20
#define COLUMN 160
int main(){
    initscr();
    noecho();
    cbreak();

    WINDOW* win = newwin(ROW + 2, COLUMN + 2, 2, 5);
	box(win, 0, 0);
	refresh();
	wrefresh(win);
    keypad(win, true);

    Market m = Market();
    int choice, highlight = 0;

    while(1){
        for(int i = 0; i<N; i++){
            if(i==highlight)
                wattron(win, A_REVERSE);
            const char * str = (m.getItem(i)) -> getSkin();
            mvwprintw(win, i+1, 1, str);
            wattroff(win, A_REVERSE);
        }

        choice = wgetch(win);
        switch(choice){
            case KEY_UP:
                highlight--;
                if(highlight == -1)
                    highlight = 0;
                break;
            case KEY_DOWN:
                highlight++;
                if(highlight == N)
                    highlight = N - 1;
                break;
            default:
                break;
        }
        if(choice == 10)
        break;
    }
    string str2 = (m.getItem(highlight)) -> getSkin();
    printw("Your choice was: %s", str2.c_str());
    refresh();
    getch();
    return 0;
}