/*----------------------------------------------------------------------------------
Implementazione della classe JumpingEnemy ("Nemico Saltellante"), 
sottoclasse di Enemy.
----------------------------------------------------------------------------------*/

#include <ncurses/ncurses.h>
#include "Enemy.h"

class JumpingEnemy: public Enemy{
    private:
        const int JUMP_FORCE = 5; //"forza di salto", ossia numero di righe che costituisce l'altezza del salto

    public:

        const int DEF_SCORE = 40;
        const int DEF_MONEY = 25;
        const int DEF_HP = 60;
        const int DEF_ST = 15;
        const int DEF_DF = 0;

        const char* enemy_shape_right[2]= {
            "  /\\__/\\ ",
            "~( =^.^=)"

        };
        const char* enemy_shape_left[2]= {
            " /\\__/\\  ",
            "(=^.^= )~"
        };

        const char* enemy_shape_right_hit[2]= {
            "  /\\__/\\ ",
            "~( =@_@=)"

        };
        const char* enemy_shape_left_hit[2]= {
            " /\\__/\\  ",
            "(=@_@= )~"
        };

        const char* enemy_shape_dead[2]= {
            "/  X X  \\",
            "VVVVVVVVV"
        };

        JumpingEnemy(WINDOW * win, int y, int x, int type, int bRight, MapManager* map, bool isL, int hp = 60, int st = 15, int df = 0, int r = 2):Enemy(win, y, x, type, bRight, map, isL, hp, st, df, r, DEF_SCORE, DEF_MONEY){
        
        }

        void jump_and_fall(){
            mv_left_right();

            if (!isJumping && !isFalling){
                isJumping = true;
                jumpCounter = jumpForce;
                jump();
            }
            else if (isJumping){
                jump();
            }
            else if (isFalling){
                fall();
            }
        }
};