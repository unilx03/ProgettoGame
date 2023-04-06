/*----------------------------------------------------------------------------------
Utilizzo della classe FlyingEnemyY (definita in FlyingEnemyY.h) per la creazione e la 
gestione delle azioni dei nemici di tipo volante che si muovono sulla stessa Y
----------------------------------------------------------------------------------*/

#include <ncurses/ncurses.h>
#include "FlyingEnemyY.h"

//Istanziazione di un nemico di tipo volante-Y; numero identificativo = 3.
//Questo tipo di nemico fluttua in aria, muovendosi a destra e a sinistra.
void create_flying_enemy_y(WINDOW * playwin, int y, int x){
        //NOTA PER ME: aggiungere la selezione randomica (fra dx e sx) della direzione di partenza del nemico
        FlyingEnemyY * e = new FlyingEnemyY(playwin, y, x, 3, 14);

        for(int i = 0; i < 100; i++){
                e->display(e->enemy_shape, e->enemy_shape);
                napms(100);
                e->mv_left_right();
        }
        
}