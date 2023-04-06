/*----------------------------------------------------------------------------------
Implementazione della classe FlyingEnemyY ("Nemico Volante" che si muove 
sulla stessa Y), sottoclasse di Enemy
----------------------------------------------------------------------------------*/

#include <ncurses/ncurses.h>
//#include "Enemy.h"
#include "ThiefEnemy.h"

class FlyingEnemyY: public Enemy{
    public:
        const char* enemy_shape[2]= {
                "___(^._.^)___",
                "Vvv  ^ ^  vvV"
        };
        
        FlyingEnemyY(WINDOW * win, int y, int x, int type, int bRight, bool isL = false, int r = 2):Enemy(win, y, x, type, bRight, isL, r){
        
        }
};

void create_flying_enemy_y(WINDOW * playwin, int y, int x);