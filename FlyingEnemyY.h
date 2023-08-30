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

        const char* enemy_shape_hit[2]= {
                "___(^@ @^)___",
                "Vvv  ^ ^  vvV"
        };

        const char* enemy_shape_dead[2]= {
                "/    X X    \\",
                "VVVVVVVVVVVVV"
        };
        
        FlyingEnemyY(WINDOW * win, int y, int x, int type, int bRight, MapManager* map, bool isL, int hp = 60, int st = 15, int df = 0, int r = 2):Enemy(win, y, x, type, bRight, map, isL, hp, st, df, r){
        
        }
};