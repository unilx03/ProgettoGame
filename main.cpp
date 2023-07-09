/*----------------------------------------------------------------------------------
Main di prova.
Path: /cygdrive/c/Users/ravy0/Documents/Università/vscodeWorkspace/Entities
Per compilare:   g++ main.cpp Hero.cpp JumpingEnemy.cpp BossEnemy.cpp -lncurses -o game
Per eseguire:   ./game.exe
----------------------------------------------------------------------------------*/

#include <ncurses/ncurses.h>
//#include "Hero.h"
//#include "Enemy.h"
//#include "JumpingEnemy.h"
//#include "ThiefEnemy.h"
//#include "FlyingEnemyY.h"
//#include "FlyingEnemyX.h"
//#include "BossEnemy.h"
#include "SetEnemiesList.h"

int main(int argc, char ** argv){
    //inizializzazione
    initscr(); //inizializza lo schermo; setta la memoria e pulisce lo schermo
    noecho();
    cbreak();
    curs_set(FALSE); //nasconde il cursore


    //imposta la dimensione dello screen
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);

    //creazione finestra
    WINDOW * playwin = newwin(20, 50, (yMax/2)-10, 10);
    box(playwin, 0, 0);
    wrefresh(playwin);

    //creazione dell'eroe
    //create_hero(playwin, 17, 1);

    //creazione di nemici
    /*
    create_jumping_enemy(playwin, 18, 25);
    create_boss_enemy(playwin, 14, 20);
    */

    //creazione lista di nemici
    p_nodo h = NULL;
    h = head_insert(h, playwin, 18, 10, 0);
    //h = head_insert(h, playwin, 18, 30, 0);
    //h = head_insert(h, playwin, 18, 25, 1);
    h = head_insert(h, playwin, 17, 35, 2);
    h = head_insert(h, playwin, 10, 20, 3);
    h = head_insert(h, playwin, 10, 25, 4);
    //h = head_insert(h, playwin, 14, 35, 5);
    
    provaaa(playwin, 17, 1, h);

    endwin(); //deallocazione della memoria e stop di ncurses 
    return 0;
}