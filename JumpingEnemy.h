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
        const char* enemy_shape_right[1]= {
            "~(=^._.^="
        };
        const char* enemy_shape_left[1]= {
            "=^._.^=)~"
        };

        JumpingEnemy(WINDOW * win, int y, int x, int type, int bRight, MapManager* map, bool isL, int hp = 4, int st = 1, int df = 1, int r = 1):Enemy(win, y, x, type, bRight, map, isL, hp, st, df, r){
        
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