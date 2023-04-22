/*----------------------------------------------------------------------------------
Implementazione della classe ThiefEnemy ("Nemico Ladro"), sottoclasse di Enemy
----------------------------------------------------------------------------------*/

#include <ncurses/ncurses.h>
//#include "Enemy.h"
#include "JumpingENemy.h"

class ThiefEnemy: public Enemy{
    public:
        const char* enemy_shape_right[2]= {
                " (O_o) ",
                "(  > )>"
        };
        const char* enemy_shape_left[2]= {
                " (o_O) ",
                "<( <  )"
        };
        
        ThiefEnemy(WINDOW * win, int y, int x, int type, int bRight, int hp = 4, int st = 1, int df = 1, bool isL = false, int r = 2):Enemy(win, y, x, type, bRight, hp, st, df, isL, r){
        
        }
};
