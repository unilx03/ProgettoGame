#include "FileManager.h"

void Menu::wrW(){
    box(this->getW(), 0, 0);
    wrefresh(this->getW());
}

void stampaConiglio(WINDOW *f, int n){
    if(n==0){
    mvwprintw(f, 3,n*45+4,"  (%c /)",92);
    mvwprintw(f, 4,n*45+4,"( ='.')");

    mvwprintw(f, 3,(n+1)*45+4,"       ");
    mvwprintw(f, 4,(n+1)*45+4,"       ");

    mvwprintw(f, 3,(n+2)*45+4,"       ");
    mvwprintw(f, 4,(n+2)*45+4,"       ");
    }
    else{
        if(n==1){
             mvwprintw(f, 3,(n-1)*45+4,"       ");
             mvwprintw(f, 4,(n-1)*45+4,"       ");

             mvwprintw(f, 3,n*45+4,"  (%c /)",92);
             mvwprintw(f, 4,n*45+4,"( ='.')");

             mvwprintw(f, 3,(n+1)*45+4,"       ");
             mvwprintw(f, 4,(n+1)*45+4,"       ");

        }
        else{
             mvwprintw(f, 3,(n-2)*45+4,"       ");
             mvwprintw(f, 4,(n-2)*45+4,"       ");

             mvwprintw(f, 3,(n-1)*45+4,"       ");
             mvwprintw(f, 4,(n-1)*45+4,"       ");

             mvwprintw(f, 3,n*45+4,"  (%c /)",92);
             mvwprintw(f, 4,n*45+4,"( ='.')");

        }
    }
}