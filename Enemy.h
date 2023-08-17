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
        const char* enemy_shape_right[1]= {
                "_( _'w')_"
        };
        const char* enemy_shape_left[1]= {
                "_('w'_ )_"
        };

        //costruttore dei nemici. Richiama il costruttore della classe Character.
        //Enemy(WINDOW * win, int y, int x, int type, int r, char* right[], char* left[]):Character(win, y, x){
        Enemy(WINDOW * win, int y, int x, int type, int bRight, MapManager* map, int hp = 4, int st = 1, int df = 1, bool isL = false, int r = 1):Character(win, y, x, bRight, map, hp, st, df, isL, r){
            //wtimeout(win, 100); //permette al nemico di muoversi indipendentemente dagli input dell'utente
            enemy_type = type;
        }

        //funzione che fa muovere i nemici a destra e a sinistra
        void mv_left_right(){
            if(is_left)
            {
                if (check_map_collision(0))
                    mvleft();
            }
            else
            {
                if (check_map_collision(1))
                    mvright();
            }
        }
};