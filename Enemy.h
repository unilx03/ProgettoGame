/*----------------------------------------------------------------------------------
Implementazione della classe Enemy ("Nemico"), sottoclasse di Character, 
e classe base delle altre classi che definiscono gli altri tipi di nemici
----------------------------------------------------------------------------------*/

#include <ncurses/ncurses.h>
#include <string.h>
#include "Hero.h"

class Enemy: public Character{

    public:
        //NOTA PER ME: aggiungere i primi due attributi tra questi al costruttore di ogni nemico
        int money_released; //soldi rilasciati dal nemico sconfitto
        int score_released; //punteggio rilasciato dal nemico sconfitto
        int enemy_type; //ogni tipo di nemico viene identificato da un numero

        const int DEF_SCORE = 25;
        const int DEF_MONEY = 10;
        const int DEF_HP = 40;
        const int DEF_ST = 15;
        const int DEF_DF = 0;

        const char* enemy_shape_right[2]= {
                "  ( )( )",
                "_( _'w')_"
        };
        const char* enemy_shape_left[2]= {
                " ( )( )  ",
                "_('w'_ )_"
        };

        const char* enemy_shape_right_hit[2]= {
                "  ( )( )",
                "_( _@.@)_"
        };
        const char* enemy_shape_left_hit[2]= {
                " ( )( )  ",
                "_(@.@_ )_"
        };

        const char* enemy_shape_dead[2]= {
                "/  X X  \\",
                "VVVVVVVVV"
        };

        //costruttore dei nemici. Richiama il costruttore della classe Character.
        Enemy(WINDOW * win, int y, int x, int type, int bRight, MapManager* map, bool isL, int hp = 40, int st = 15, int df = 0, int r = 2, int score_rel = 25, int money_rel = 10):Character(win, y, x, bRight, map, isL, hp, st, df, r){
            //wtimeout(win, 100); //permette al nemico di muoversi indipendentemente dagli input dell'utente
            enemy_type = type;
            money_released = money_rel;
            score_released = score_rel;
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

        //Funzione che controlla se un nemico è venuto a contatto con il personaggino.
        void check_enemy_player_collision(Hero *p){
            //se il nemico colpisce l'eroe da dx, quest'ultimo viene "spinto" verso sx
            if((p->xLoc >= xLoc - p->bound_right+1 && p->xLoc < xLoc) && (p->yLoc >= yLoc && p->yLoc <= yLoc + rows)){
                p->is_hit = true;
                p->hit_direction = 1;
                if (p->check_map_collision(0))
                    p->mvleft();
                if (p->check_map_collision(3))
                    p->isFalling = true;
            }
            //se il nemico colpisce l'eroe da sx, quest'ultimo viene "spinto" verso dx
            else if((p->xLoc == xLoc + bound_right - 2) && (p->yLoc >= yLoc && p->yLoc <= yLoc + rows)){
                p->is_hit = true;
                p->hit_direction = 2;
                if (p->check_map_collision(1))
                    p->mvright();
                if (p->check_map_collision(3))
                    p->isFalling = true;
            }
            //se il nemico colpisce l'eroe dal basso, quest'ultimo viene "fatto rimbalzare" verso l'alto; se l'eroe sta eseguendo un attacco dall'alto, allora è il nemico a subire danno
            else if((p->xLoc >= xLoc - p->bound_right+2 && p->xLoc <= xLoc + bound_right - 3) && (p->yLoc + p->rows == yLoc)){
                if(!(p->isAttackingDown)){
                    p->is_hit = true;
                    p->hit_direction = 3;
                    p->isJumping = true;
                    p->isFalling = false;
                    p->jumpCounter = p->jumpForce;
                    p->jump();
                }
                else{
                    hit_direction = 4;
                    setHealth(getHealth() - p->getStrenght() + getDefense());
                    if(getHealth() <= 0){
                        //l'eroe guadagna soldi e punteggio
                        p->setMoney(p->getMoney() + money_released);
                        p->score += score_released;
                    }
                    else{
                        //l'eroe guadagna un pochino di punteggio
                        p->score += score_released/5;
                    }
                    p->isAttackingDown = false;
                    
                    p->isJumping = true;
                    p->isFalling = false;
                    p->jumpCounter = p->jumpForce;
                    p->jump();
                }
            }
            //se il nemico colpisce l'eroe dall'alto, quest'ultimo viene "fatto rimbalzare" verso il basso
            else if((p->xLoc >= xLoc - p->bound_right+2 && p->xLoc <= xLoc + bound_right - 3) && (p->yLoc == yLoc + rows)){
                p->is_hit = true;
                p->hit_direction = 4;
                p->isJumping = false;
                p->isFalling = true;
                p->fall();
            }
            
            //Se l'eroe è entrato a contatto con un nemico, perde tanti punti vita (health) quanti sono i punti di forza (strenght) del nemico
            if(enemy_type!=2 && p->is_hit && getHealth()>0){ //per una iterazione, il nemico morto rimane visibile sottoforma di fantasma; in quel contesto non è però in grado di causare danno all'eroe. Per questo devo controllare getHealth().
                p->setHealth(p->getHealth() - getStrenght() + p->getDefense());
                p->is_hit = false;
            }
            else if(enemy_type==2 && p->is_hit && getHealth()>0){ //nel caso in cui l'eroe venga a contatto con un nemico di tipo ladro, perde soldi invece che punti vita
                p->setMoney(p->getMoney() - getStrenght());
                if(p->getMoney()<0)
                    p->setMoney(0);
                p->is_hit = false;
            }
        }

        //Funzione che controlla se un nemico è venuto a contatto con un proiettile.
        Hero::p_bullet check_enemy_bullet_collision(Hero *p, Hero::p_bullet h){
            
            is_hit = false;

            if(h != NULL){
                int y = yLoc;
                int x_sx = xLoc-2, x_dx = xLoc+bound_right-1;

                //controllo il primo proiettile della lista di proiettili
                while(y < yLoc+rows && !is_hit){
                    if((h->bullet_x >= x_sx && h->bullet_x <= x_dx) && h->bullet_y == y){
                        is_hit = true;
                        hit_direction = 1;
                        setHealth(getHealth() - p->getStrenght() + getDefense());

                        //rimuovo il proiettile
                        Hero::p_bullet h2 = h;
                        h = h->next;
                        delete(h2);

                        if(getHealth() <= 0){
                            //l'eroe guadagna soldi e punteggio
                            p->setMoney(p->getMoney() + money_released);
                            p->score += score_released;
                        }
                        else{
                            //l'eroe guadagna un pochino di punteggio
                            p->score += score_released/5;
                        }
                    }
                    y++;
                }
                //controllo dal secondo proiettile in poi
                Hero::p_bullet tmp = h;
                while(tmp!=NULL && (tmp->next)!=NULL){
                    is_hit = false;
                    y = yLoc;
                    while(y < yLoc+rows && !is_hit){
                        if(((tmp->next)->bullet_x >= x_sx && (tmp->next)->bullet_x <= x_dx) && (tmp->next)->bullet_y == y){    //se il nemico viene colpito da dx
                            is_hit = true;
                            hit_direction = 1;

                            //rimuovo il proiettile
                            Hero::p_bullet tmp2 = tmp->next;
                            tmp->next = (tmp->next)->next;
                            delete tmp2;
                        }
                        y++;
                    }

                    if(is_hit){
                        setHealth(getHealth() - p->getStrenght() + getDefense());
                        
                        if(getHealth() <= 0){
                            //l'eroe guadagna soldi e punteggio
                            p->setMoney(p->getMoney() + money_released);
                            p->score += score_released;
                        }
                        else{
                            //l'eroe guadagna un pochino di punteggio
                            p->score += score_released/5;
                        }
                    }
                    else{
                        tmp = tmp->next;
                    }
                }
            }
            return h;
        }

};