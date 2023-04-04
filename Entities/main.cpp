/*----------------------------------------------------------------------------------
Main di prova.
Path: /cygdrive/c/Users/ravy0/Documents/Università/vscodeWorkspace/Entities
Per compilare:   g++ main.cpp Character.cpp Hero.cpp Enemy.cpp JumpingEnemy.cpp ThiefEnemy.cpp FlyingEnemyY.cpp FLyingEnemyX.cpp BossEnemy.cpp -lncurses -o game
Per eseguire:   ./game.exe
----------------------------------------------------------------------------------*/

#include <ncurses/ncurses.h>
//#include "Hero.h"
//#include "Enemy.h"
//#include "JumpingEnemy.h"
//#include "ThiefEnemy.h"
//#include "FlyingEnemyY.h"
//#include "FlyingEnemyX.h"
#include "BossEnemy.h"

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
    create_hero(playwin, 17, 1);

    //creazione di nemici
    /*create_standard_enemy(playwin, 18, 10);
    create_jumping_enemy(playwin, 18, 25);
    create_thief_enemy(playwin, 17, 35);
    create_flying_enemy_y(playwin, 10, 15);
    create_flying_enemy_x(playwin, 10, 20);
    create_boss_enemy(playwin, 14, 20);*/

    endwin(); //deallocazione della memoria e stop di ncurses 
    return 0;
}