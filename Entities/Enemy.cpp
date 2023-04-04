/*----------------------------------------------------------------------------------
Utilizzo della classe Enemy (definita in Enemy.h) per la creazione e la gestione 
delle azioni dei nemici
----------------------------------------------------------------------------------*/

#include <ncurses/ncurses.h>
#include "Enemy.h"

//Istanziazione di un nemico di tipo standard (nemico base); numero identificativo = 0.
//Questo tipo di nemico si muove a destra e a sinistra.
void create_standard_enemy(WINDOW * playwin, int y, int x){
        //NOTA PER ME: aggiungere la selezione randomica (fra dx e sx) della direzione di partenza del nemico
        Enemy * e = new Enemy(playwin, y, x, 0, 10);

        for(int i = 0; i < 100; i++){
                e->display(e->enemy_shape_left, e->enemy_shape_right);
                napms(100);
                e->mv_left_right();
        }
        
}