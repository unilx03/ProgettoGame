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

        //Funzione che controlla se un nemico è venuto a contatto con il personaggino. (DA FINIRE!!)
        //bool check_enemy_player_collision(Hero *p){
        void check_enemy_player_collision(Hero *p){
            //bool not_hit = true;

            //se il nemico colpisce l'eroe da dx, quest'ultimo viene "spinto" verso sx
            if((p->xLoc >= xLoc - p->bound_right+1 && p->xLoc < xLoc) && (p->yLoc >= yLoc && p->yLoc <= yLoc + rows)){
                //not_hit = false;
                p->is_hit = true;
                p->hit_direction = 1;
                if (p->check_map_collision(0))
                    p->mvleft();
                if (p->check_map_collision(3))
                    p->isFalling = true;
            }
            //se il nemico colpisce l'eroe da sx, quest'ultimo viene "spinto" verso dx
            else if((p->xLoc == xLoc + bound_right - 2) && (p->yLoc >= yLoc && p->yLoc <= yLoc + rows)){
                //not_hit = false;
                p->is_hit = true;
                p->hit_direction = 2;
                if (p->check_map_collision(1))
                    p->mvright();
                if (p->check_map_collision(3))
                    p->isFalling = true;
            }
            //se il nemico colpisce l'eroe dal basso, quest'ultimo viene "fatto rimbalzare" verso l'alto
            else if((p->xLoc >= xLoc - p->bound_right+2 && p->xLoc <= xLoc + bound_right - 3) && (p->yLoc + p->rows == yLoc)){
                //not_hit = false;
                p->is_hit = true;
                p->hit_direction = 3;
                p->isJumping = true;
                p->isFalling = false;
                p->jumpCounter = p->jumpForce;
                p->jump();
            }
            //se il nemico colpisce l'eroe dall'alto, quest'ultimo viene "fatto rimbalzare" verso il basso
            else if((p->xLoc >= xLoc - p->bound_right+2 && p->xLoc <= xLoc + bound_right - 3) && (p->yLoc == yLoc + rows)){
                //not_hit = false;
                p->is_hit = true;
                p->hit_direction = 4;
                p->isJumping = false;
                p->isFalling = true;
                p->fall();
            }
            
            //Se l'eroe è entrato a contatto con un nemico, perde tanti punti vita (health) quanti sono i punti di forza (strenght) del nemico
            if(p->is_hit){
                p->setHealth(p->getHealth() - getStrenght());
                p->is_hit = false;
    	        //p->hit_direction = 0;
            }
            
            //return not_hit;
        }

        //Funzione che controlla se un nemico è venuto a contatto con un proiettile. In tal caso, enemy->setHealth(enemy->getHealth - player->strenght. Se arrivo a 0, rimuovere il nemico dalla lista)
        //NOTA: probabilmente questa funzione andrà spostata in SetEnemiesList.h
};