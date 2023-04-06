/*----------------------------------------------------------------------------------
Implementazione della classe Hero ("Eroe", il personaggio comandato dall'utente), 
sottoclasse di Character
----------------------------------------------------------------------------------*/

#include <ncurses/ncurses.h>
//#include "JumpingEnemy.h"
#include "Character.h"

class Hero: public Character{
    public:
        //NOTA PER ME: aggiungere i seguenti attributi commentati al costruttore ecc.
        //char player_name[50]; //nome del giocatore, che apparirà accanto all'highscore
        //diff_level //livello di difficoltà
        //money //denaro accumulato uccidendo i nemici
        //score //punteggio accumulato durante la partita

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
        Hero(WINDOW * win, int y, int x, int bRight, bool isL = false, int r = 2):Character(win, y, x, bRight, isL, r){
            
        }

        //Al momento il funzionamento è questo:
        //default -> salto verticale, 
        //freccia su + freccia dx/sx -> salto dx/sx
        //freccia su + barra spaziatrice -> attacco durante il salto
        void get_jump_type(){
            int choice = wgetch(curwin);
            wtimeout(curwin, 250); //dopo aver premuto la freccia in su, se l'utente non preme nessun altro tasto entro 250ms, il personaggio fa un semplice salto in verticale
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
                    break;
                case KEY_RIGHT:
                    mvright();
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