/*----------------------------------------------------------------------------------
Implementazione della classe JumpingEnemy ("Nemico Saltellante"), 
sottoclasse di Enemy.
----------------------------------------------------------------------------------*/

#include <ncurses/ncurses.h>
#include "Enemy.h"

class JumpingEnemy: public Enemy{
    private:
        const int JUMP_DELAY = 45; 
        const int JUMP_FORCE = 5; //"forza di salto", ossia numero di righe che costituisce l'altezza del salto

    public:
    
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

        JumpingEnemy(WINDOW * win, int y, int x, int type, int bRight, MapManager* map, bool isL, int hp = 4, int st = 1, int df = 1, int r = 2):Enemy(win, y, x, type, bRight, map, isL, hp, st, df, r){
        
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