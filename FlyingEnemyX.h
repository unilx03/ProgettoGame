/*----------------------------------------------------------------------------------
Implementazione della classe FlyingEnemyX ("Nemico Volante" che si muove sulla 
stessa X), sottoclasse di Enemy
----------------------------------------------------------------------------------*/

#include <ncurses/ncurses.h>
//#include "Enemy.h"
#include "FlyingEnemyY.h"

class FlyingEnemyX: public Enemy{
    public:
        //la seguente variabile booleana serve per memorizzare quale è stata l'ultima direzione presa dal nemico (se su o giù)
        bool is_up;

        const int DEF_SCORE = 20;
        const int DEF_MONEY = 10;
        const int DEF_HP = 40;
        const int DEF_ST = 10;
        const int DEF_DF = 0;

        const char* enemy_shape[3]= {
                " ,__,",
                "(O,O)",
                "/),,)"
        };

        const char* enemy_shape_hit[3]= {
                " ,__,",
                "(@<@)",
                "/),,)"
        }; 

        const char* enemy_shape_dead[3]= {
                "/X X\\",
                "|   |",
                "VVVVV"
        };        
        
        FlyingEnemyX(WINDOW * win, int y, int x, int type, int bRight, MapManager* map, bool isL, int hp = 40, int st = 10, int df = 0, int r = 3):Enemy(win, y, x, type, bRight, map, isL, hp, st, df, r, DEF_SCORE, DEF_MONEY){
            is_up = true; 
        }
        void mvup();
        void mvdown();
        void mv_up_down();
        bool check_map_collision(int direction);
};