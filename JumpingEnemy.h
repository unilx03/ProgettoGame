/*----------------------------------------------------------------------------------
Implementazione della classe JumpingEnemy ("Nemico Saltellante"), 
sottoclasse di Enemy.
----------------------------------------------------------------------------------*/

#include <ncurses.h>
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

        JumpingEnemy(WINDOW * win, int y, int x, int type, int bRight, MapManager* map, int hp = 4, int st = 1, int df = 1, bool isL = false, int r = 1):Enemy(win, y, x, type, bRight, map, hp, st, df, isL, r){

        }
};

void create_jumping_enemy(WINDOW * playwin, int y, int x);