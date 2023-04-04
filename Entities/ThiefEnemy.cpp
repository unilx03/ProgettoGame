/*----------------------------------------------------------------------------------
Utilizzo della classe ThiefEnemy (definita in ThiefEnemy.h) per la creazione e la 
gestione delle azioni dei nemici di tipo ladro
----------------------------------------------------------------------------------*/

#include <ncurses/ncurses.h>
#include "ThiefEnemy.h"

//Istanziazione di un nemico di tipo ladro; numero identificativo = 2.
//Questo tipo di nemico è simile a quello deinito dalla classe base Enemy, ma il giocatore perde soldi invece che punteggio a contatto con esso.
void create_thief_enemy(WINDOW * playwin, int y, int x){
        //NOTA PER ME: aggiungere la selezione randomica (fra dx e sx) della direzione di partenza del nemico
        ThiefEnemy * e = new ThiefEnemy(playwin, y, x, 2, 8);

        for(int i = 0; i < 100; i++){
                e->display(e->enemy_shape_left, e->enemy_shape_right);
                napms(100);
                e->mv_left_right();
        }
        
}