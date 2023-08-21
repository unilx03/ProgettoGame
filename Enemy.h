/*----------------------------------------------------------------------------------
Implementazione della classe Enemy ("Nemico"), sottoclasse di Character, 
e classe base delle altre classi che definiscono gli altri tipi di nemici
----------------------------------------------------------------------------------*/

#include <ncurses/ncurses.h>
//#include "Character.h"
#include "Hero.h"

class Enemy: public Character{

    public:
        //NOTA PER ME: aggiungere i seguenti attributi commentati al costruttore ecc.
        //damage //danni inflitti al giocatore (dipendono dall'attributo diff_level dell'eroe)
        //money_released //soldi rilasciati alla sconfitta (dipendono dall'attributo diff_level dell'eroe)
        //score_released

        //ogni tipo di nemico viene identificato da un numero
        int enemy_type;

        //il personaggio viene disegnato su più righe utilizzando un array
        /*const char* enemy_shape_right[1]= {
                "_( _'w')_"
        };
        const char* enemy_shape_left[1]= {
                "_('w'_ )_"
        };*/

        const char* enemy_shape_right[2]= {
                "  ( )( )",
                "_( _'w')_"
        };
        const char* enemy_shape_left[2]= {
                " ( )( )  ",
                "_('w'_ )_"
        };

        //costruttore dei nemici. Richiama il costruttore della classe Character.
        //Enemy(WINDOW * win, int y, int x, int type, int r, char* right[], char* left[]):Character(win, y, x){
        Enemy(WINDOW * win, int y, int x, int type, int bRight, MapManager* map, bool isL, int hp = 4, int st = 1, int df = 1, int r = 2):Character(win, y, x, bRight, map, isL, hp, st, df, r){
            //wtimeout(win, 100); //permette al nemico di muoversi indipendentemente dagli input dell'utente
            enemy_type = type;
        }

        //funzione che fa muovere i nemici a destra e a sinistra
        void mv_left_right(){
            if (isFalling){
                fall();
            }

            if(is_left)
            {
                if (check_map_collision(0))
                    mvleft();
                else
                    is_left = false;

                if (enemy_type != 3 && check_map_collision(3))
                    isFalling = true;

                /*if (enemy_type != 3 && enemy_type != 0 && check_map_collision(3))
                    isFalling = true;
                else if (enemy_type == 0 && check_map_collision(3))
                    is_left = false;*/
            }
            else
            {
                if (check_map_collision(1))
                    mvright();
                else
                    is_left = true;

                if (enemy_type != 3 && check_map_collision(3))
                    isFalling = true;

                /*if (enemy_type != 3 && enemy_type != 0 && check_map_collision(3))
                    isFalling = true;
                else if (enemy_type == 0 && check_map_collision(3))
                    is_left = true;*/
            }
        }
};