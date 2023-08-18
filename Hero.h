/*----------------------------------------------------------------------------------
Implementazione della classe Hero ("Eroe", il personaggio comandato dall'utente), 
sottoclasse di Character
----------------------------------------------------------------------------------*/

#include <ncurses/ncurses.h>
#include <cstring>
#include "Character.h"

class Hero: public Character{
    private:
        //attributi su cui avranno influenza gli oggetti
        int money; 
        int luck; //punti fortuna (determinano la probabilità di trovare determinati oggetti nei livelli)
        bool invincibility;
        bool doubleMoney;
        bool doubleScore;

    public:
        //NOTA PER ME: aggiungere i seguenti attributi commentati al costruttore ecc.
        //diff_level //livello di difficoltà

        char player_name[50]; //nome del giocatore, che apparirà accanto all'highscore
        int score; //punteggio accumulato durante la partita

        void setMoney(int n){
            money = n;
        }
        int getMoney(){
            return money;
        }
        void setLuck(int n){
            luck = n;
        }
        int getLuck(){
            return luck;
        }
        void setInvincibility(bool b){
            invincibility = b;
        }
        bool getInvincibility(){
            return invincibility;
        }
        void setDoubleMoney(bool b){
            doubleMoney = b;
        }
        bool getDoubleMoney(){
            return doubleMoney;
        }
        void setDoubleScore(bool b){
            doubleScore = b;
        }
        bool getDoubleScore(){
            return doubleScore;
        }

        //NOTA PER ME: per far perdere punteggio al giocatore, si potrebbe controllare se hero.xLoc == enemy.xLoc o simile

        //il personaggio viene disegnato su più righe utilizzando un array
        const char* player_shape_right[2] = {
            "  (\\ /)",
            "( ='.')",
        };
        const char* player_shape_left[2] = {
            "(\\ /) ",
            "('.'= )",
        };

        //costruttore del personaggio
        Hero(WINDOW * win, int y, int x, int bRight, MapManager* map, bool isL, char n[], int hp = 5, int st = 3, int df = 1, int r = 2, int m = 0, int s = 0, int lp = 0, bool inv = false, bool dM = false, bool dS = false):Character(win, y, x, bRight, map, isL, hp, st, df, r){
            money = m;
            score = s;
            luck = lp;
            strcpy(player_name, n);
            invincibility = inv;
            doubleMoney = dM;
            doubleScore = dS;
        }

        //switch-case per gestire le mosse del personaggio in base al tasto premuto dall'utente
        void getmv(int choice){

            //napms(50);

            if (isJumping){
                jump();
            }
            else if (isFalling){
                fall();
            }

            if(isAttacking){
                attack();
            }
            
            switch(choice){
                case KEY_UP:
                    if (!isJumping && !isFalling)
                    {
                        isJumping = true;
                        jumpCounter = jumpForce;
                        jump();
                    }
                    break;
                case KEY_LEFT:
                    if (check_map_collision(0))
                        mvleft();

                    if (check_map_collision(3))
                        isFalling = true;
                    //napms(70); //tentativo di non velocizzare tutti i nemici quando si tiene premuta una freccia
                    break;
                case KEY_RIGHT:
                    if (check_map_collision(1))
                        mvright();

                    if (check_map_collision(3))
                        isFalling = true;
                    //napms(70); //tentativo di non velocizzare tutti i nemici quando si tiene premuta una freccia
                    break;
                case ' ': //quando si preme la barra spaziatrice
                    if(!isAttacking){
                        isAttacking = true;
                        bullet_y = yLoc;
                        if(is_left){
                            is_left_bullet = true;
                            bullet_x = xLoc;
                        }
                        else{
                            is_left_bullet = false;
                            bullet_x = xLoc+bound_right-1;
                        }
                        attack();
                    }
                    break;
                default:
                    if (isJumping){
                        jump();
                    }
                    else if (isFalling){
                        fall();
                    }

                    if(isAttacking){
                        attack();
                    }
                    break;
            }
        }
};