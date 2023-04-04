/*----------------------------------------------------------------------------------
Utilizzo della classe FlyingEnemyX (definita in FlyingEnemyX.h) per la creazione e la 
gestione delle azioni dei nemici di tipo volante che si muovono sulla stessa X
----------------------------------------------------------------------------------*/

#include <ncurses/ncurses.h>
#include "BossEnemy.h"

//Istanziazione di un nemico di tipo boss; numero identificativo = 5.
//Questo tipo di nemico fluttua in aria, muovendosi su e giù.
void create_boss_enemy(WINDOW * playwin, int y, int x){
        //NOTA PER ME: aggiungere la selezione randomica (fra dx e sx) della direzione di partenza del nemico
        BossEnemy * e = new BossEnemy(playwin, y, x, 5, 11);

        //for(int i = 0; i < 100; i++){
                e->display(e->enemy_shape, e->enemy_shape);
                napms(5000);
                //e->attack(); //spara proiettili
        //}
        
}