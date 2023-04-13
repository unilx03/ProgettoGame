/*----------------------------------------------------------------------------------
Utilizzo della classe JumpingEnemy (definita in JumpingEnemy.h) per la 
creazione e la gestione delle azioni dei nemici "saltellanti"
----------------------------------------------------------------------------------*/

#include <ncurses/ncurses.h>
#include "JumpingEnemy.h"

//Istanziazione di un nemico di tipo saltellante; numero identificativo = 1.
//Questo tipo di nemico si muove a destra e a sinistra saltando.
void create_jumping_enemy(WINDOW * playwin, int y, int x){
        //NOTA PER ME: aggiungere la selezione randomica (fra dx e sx) della direzione di partenza del nemico, + selezione randomica di quando farlo saltare
        JumpingEnemy * e = new JumpingEnemy(playwin, y, x, 1, 10);

        for(int i = 0; i < 20; i++){
                e->display(e->enemy_shape_left, e->enemy_shape_right);
                napms(100);
                e->jump(e->enemy_shape_left, e->enemy_shape_right);
        }
        
}