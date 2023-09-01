/*----------------------------------------------------------------------------------
Implementazione della classe ThiefEnemy ("Nemico Ladro"), sottoclasse di Enemy
----------------------------------------------------------------------------------*/

#include <ncurses/ncurses.h>
//#include "Enemy.h"
#include "JumpingEnemy.h"

class ThiefEnemy: public Enemy{
    public:

        const int DEF_SCORE = 15;
        const int DEF_MONEY = 10;
        const int DEF_HP = 30;
        const int DEF_ST = 3;
        const int DEF_DF = 0;

        const char* enemy_shape_right[2]= {
                " (O_o) ",
                "(  > )>"
        };
        const char* enemy_shape_left[2]= {
                " (o_O) ",
                "<( <  )"
        };

        const char* enemy_shape_right_hit[2]= {
                " (X.x) ",
                "(  > )>"
        };
        const char* enemy_shape_left_hit[2]= {
                " (x.X) ",
                "<( <  )"
        };

        const char* enemy_shape_dead[2]= {
                "/ X X \\",
                "VVVVVVV"
        };
        
        ThiefEnemy(WINDOW * win, int y, int x, int type, int bRight, MapManager* map, bool isL, int hp = 30, int st = 3, int df = 0, int r = 2):Enemy(win, y, x, type, bRight, map, isL, hp, st, df, r, DEF_SCORE, DEF_MONEY){
        
        }
};
