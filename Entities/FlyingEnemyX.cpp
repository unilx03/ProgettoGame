/*----------------------------------------------------------------------------------
Utilizzo della classe FlyingEnemyX (definita in FlyingEnemyX.h) per la creazione e la 
gestione delle azioni dei nemici di tipo volante che si muovono sulla stessa X
----------------------------------------------------------------------------------*/

#include <ncurses/ncurses.h>
#include "FlyingEnemyX.h"

//Istanziazione di un nemico di tipo volante-X; numero identificativo = 4.
//Questo tipo di nemico fluttua in aria, muovendosi su e giù.
void create_flying_enemy_x(WINDOW * playwin, int y, int x){
        //NOTA PER ME: aggiungere la selezione randomica (fra dx e sx) della direzione di partenza del nemico
        FlyingEnemyX * e = new FlyingEnemyX(playwin, y, x, 3, 6, true);

        for(int i = 0; i < 100; i++){
                e->display(e->enemy_shape, e->enemy_shape);
                napms(100);
                e->mv_up_down();
        }
        
}