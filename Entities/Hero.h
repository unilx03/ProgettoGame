/*----------------------------------------------------------------------------------
Implementazione della classe Hero ("Eroe", il personaggio comandato dall'utente), 
sottoclasse di Character
----------------------------------------------------------------------------------*/

#include <ncurses.h>
#include <cstring>
//#include "JumpingEnemy.h"
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
            "(\\ /)  ",
            "('.'= )",
        };

        //costruttore del personaggio
        Hero(WINDOW * win, int y, int x, int bRight, char n[], int hp = 5, int st = 3, int df = 1, bool isL = false, int r = 2, int m = 0, int s = 0, int lp = 0, bool inv = false, bool dM = false, bool dS = false):Character(win, y, x, bRight, hp, st, df, isL, r){
            money = m;
            score = s;
            luck = lp;
            strcpy(player_name, n);
            invincibility = inv;
            doubleMoney = dM;
            doubleScore = dS;
        }

        //default -> salto in verticale
        //freccia su + freccia dx/sx -> salto a dx/sx
        //freccia su + barra spaziatrice -> attacco durante il salto
        void get_jump_type(){
            int choice = wgetch(curwin);
            wtimeout(curwin, 150); //dopo aver premuto la freccia in su, se l'utente non preme nessun altro tasto entro 150ms, il personaggio fa un semplice salto in verticale
            switch(choice){
                case KEY_LEFT:
                    is_left = true;
                    jump(player_shape_left, player_shape_right);
                    fall(player_shape_left, player_shape_right);
                    break;
                case KEY_RIGHT:
                    is_left = false;
                    jump(player_shape_left, player_shape_right);
                    fall(player_shape_left, player_shape_right);
                    break;
                case ' ': //quando si preme la barra spaziatrice
                    jump_vertical(player_shape_left, player_shape_right);
                    attack(player_shape_left, player_shape_right);
                    fall_vertical(player_shape_left, player_shape_right);
                    break;
                default:
                    jump_vertical(player_shape_left, player_shape_right);
                    fall_vertical(player_shape_left, player_shape_right);
                    break;
            }
        }

        //switch-case per gestire le mosse del personaggio in base al tasto premuto dall'utente
        int getmv(){
            int choice = wgetch(curwin);
            switch(choice){
                /*case KEY_UP:
                    jump(player_shape_left, player_shape_right);
                    break;*/
                case KEY_UP:
                    get_jump_type();
                    break;
                case KEY_LEFT:
                    mvleft();
                    //napms(70); //tentativo di non velocizzare tutti i nemici quando si tiene premuta una freccia
                    break;
                case KEY_RIGHT:
                    mvright();
                    //napms(70); //tentativo di non velocizzare tutti i nemici quando si tiene premuta una freccia
                    break;
                case ' ': //quando si preme la barra spaziatrice
                    attack(player_shape_left, player_shape_right);
                    break;
                default:
                    break;
            }
            return choice;
        }

};

void create_hero(WINDOW * playwin, int y, int x);