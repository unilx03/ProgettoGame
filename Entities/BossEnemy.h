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
        
        BossEnemy(WINDOW * win, int y, int x, int type, int bRight, int hp = 4, int st = 1, int df = 1, bool isL = false, int r = 5):Enemy(win, y, x, type, bRight, hp, st, df, isL, r){
            
        }

       
};

void create_boss_enemy(WINDOW * playwin, int y, int x);