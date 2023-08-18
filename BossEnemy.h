/*----------------------------------------------------------------------------------
Implementazione della classe BossEnemy ("Boss")
----------------------------------------------------------------------------------*/

#include <ncurses/ncurses.h>
//#include "Enemy.h"
#include "FlyingEnemyX.h"

class BossEnemy: public Enemy{
    public:
        const char* enemy_shape[5]= {
                " /\\___/\\ ",
                "= .\\ /. =",
                " = (Y) = ",
                "(\")| |(\")",
                " (\") (\") "
        };
        
        BossEnemy(WINDOW * win, int y, int x, int type, int bRight, MapManager* map, bool isL, int hp = 4, int st = 1, int df = 1, int r = 5):Enemy(win, y, x, type, bRight, map, isL, hp, st, df, r){
            
        }

       
};

void create_boss_enemy(WINDOW * playwin, int y, int x);