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
        
        FlyingEnemyX(WINDOW * win, int y, int x, int type, int bRight, MapManager* map, bool isL, int hp = 40, int st = 10, int df = 0, bool up = true, int r = 3):Enemy(win, y, x, type, bRight, map, isL, hp, st, df, r){
            is_up = up;
        }

        //Spostamento in su del nemico
        void mvup(){
            is_up = true;
            yLoc--;
            if(yLoc < 1){
                yLoc = 1;
                is_up = false;
            }
        }

        //Spostamento in giù del nemico
        void mvdown(){
            is_up = false;
            yLoc++;
            if(yLoc > yMax-(rows+1)){
                yLoc = yMax-(rows+1);
                is_up = true;
            }
        }

        //funzione che fa muovere il nemico su e giù
        void mv_up_down(){
            if(is_up)
            {
                if (check_map_collision(2))
                    mvup();
                else
                    is_up = false;
            }
            else
            {
                if (check_map_collision(3))
                    mvdown();
                else
                    is_up = true;
            }
        }
};