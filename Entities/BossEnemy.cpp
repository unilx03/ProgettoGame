/*----------------------------------------------------------------------------------
Utilizzo della classe FlyingEnemyX (definita in FlyingEnemyX.h) per la creazione e la 
gestione delle azioni dei nemici di tipo volante che si muovono sulla stessa X
----------------------------------------------------------------------------------*/

#include <ncurses/ncurses.h>
#include "BossEnemy.h"

//Istanziazione di un nemico di tipo boss; numero identificativo = 5.
//Questo tipo di nemico fluttua in aria, muovendosi su e giù.
void create_boss_enemy(WINDOW * playwin, int y, int x){
        //NOTA PER ME: il boss deve attaccare nella direzione e alla'altezza in cui si trova il personaggino
        BossEnemy * e = new BossEnemy(playwin, y, x, 5, 11);

        for(int i = 0; i < 5; i++){
                e->is_left = true;
                e->display(e->enemy_shape, e->enemy_shape);
                e->attack(e->enemy_shape, e->enemy_shape);
                e->is_left = false;
                e->attack(e->enemy_shape, e->enemy_shape);
        }
        
}