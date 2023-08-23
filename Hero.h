/*----------------------------------------------------------------------------------
Implementazione della classe Hero ("Eroe", il personaggio comandato dall'utente), 
sottoclasse di Character
----------------------------------------------------------------------------------*/

#include <ncurses/ncurses.h>
#include <cstring>
#include "Character.h"

class Hero: public Character{
    private:

       //I proiettili vengono gestiti tramite una lista. Ciò permette all'eroe di sparare più proiettili per volta.
        struct bulletNode{    
            int bullet_x=0;
            int bullet_y=0;
            bool is_left_bullet; //direzione del proiettile
            bulletNode *next;
        };
        typedef bulletNode* p_bullet;
        p_bullet h = NULL;
        const char* bullet = "-";
        bool isAttacking; //è vero finchè la lista di proiettili ha almeno un elemento

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
            "( ='.')"
        };
        const char* player_shape_left[2] = {
            "(\\ /) ",
            "('.'= )"
        };

        const char* player_shape_right_hit[2] = {
            "  (\\ /)",
            "( =@_@)"
        };
        const char* player_shape_left_hit[2] = {
            "(\\ /) ",
            "(@_@= )"
        };
        const char* player_shape_dead[2] = {
            "/ X X \\",
            "VVVVVVV"
        };

        //costruttore del personaggio
        Hero(WINDOW * win, int y, int x, int bRight, MapManager* map, bool isL, char n[], int hp = 25, int st = 1, int df = 1, int r = 2, int m = 0, int s = 0, int lp = 0, bool inv = false, bool dM = false, bool dS = false):Character(win, y, x, bRight, map, isL, hp, st, df, r){
            money = m;
            score = s;
            luck = lp;
            strcpy(player_name, n);
            invincibility = inv;
            doubleMoney = dM;
            doubleScore = dS;
            isAttacking = false;
        }

        //********** Nella seguente sezione si gestisce l'attacco con i proiettili **********

        //Funzione che inserisce un nuovo proiettile in testa alla lista
        p_bullet bullet_insert(p_bullet h, int x, int y, bool left){
            p_bullet tmp = new bulletNode;
            tmp->bullet_x = x;
            tmp->bullet_y = y;
            tmp->is_left_bullet = left;
            tmp->next = h;
            return tmp;
        }

        //Funzione di attacco (permette al personaggio di "sparare proiettili") (NOTA: dà coredump)
        p_bullet attack(p_bullet h){
            if(isAttacking){
                if(h == NULL) //controllo se ci sono ancora proiettili nella lista
                    isAttacking = false;
                else{
                    //check del primo elemento
                    if(h->is_left_bullet){
                        if(h->bullet_x > 1 && check_map_collision_bullet(h->is_left_bullet, h->bullet_y, h->bullet_x)){
                            h->bullet_x--;
                            mvwprintw(curwin, h->bullet_y, h->bullet_x, bullet);
                        }
                        else{
                            //rimuovo il proiettile dalla lista                                
                            p_bullet h2 = h;
                            h = h->next;
                            delete(h2);
                        }
                    }
                    else{
                        if(h->bullet_x < xMax-1 && check_map_collision_bullet(h->is_left_bullet, h->bullet_y, h->bullet_x)){
                                h->bullet_x++;
                                mvwprintw(curwin, h->bullet_y, h->bullet_x, bullet);
                        }
                        else{
                            //rimuovo il proiettile dalla lista
                            p_bullet h2 = h;
                            h = h->next;
                           delete(h2);
                        }
                    }

                    //check dal secondo elemento in poi
                    p_bullet tmp = h;
                    while(tmp!=NULL && (tmp->next)!=NULL){
                        if((tmp->next)->is_left_bullet){
                            if((tmp->next)->bullet_x > 1 && check_map_collision_bullet((tmp->next)->is_left_bullet, (tmp->next)->bullet_y, (tmp->next)->bullet_x)){
                                (tmp->next)->bullet_x--;
                                mvwprintw(curwin, (tmp->next)->bullet_y, (tmp->next)->bullet_x, bullet);
                                tmp = tmp->next;
                            }
                            else{
                                //rimuovo il proiettile dalla lista (FARE UNA FUNZIONE APPOSTA!! così stai solo evitando di stampare i proiettili che hanno colpito qualcosa)
                                p_bullet tmp2 = tmp->next;
                                tmp->next = (tmp->next)->next;
                                delete tmp2;
                            }
                        }
                        else{
                            if((tmp->next)->bullet_x < xMax-1 && check_map_collision_bullet((tmp->next)->is_left_bullet, (tmp->next)->bullet_y, (tmp->next)->bullet_x)){
                                (tmp->next)->bullet_x++;
                                mvwprintw(curwin, (tmp->next)->bullet_y, (tmp->next)->bullet_x, bullet);
                                tmp = tmp->next;
                            }
                            else{
                               //rimuovo il proiettile dalla lista (FARE UNA FUNZIONE APPOSTA!! così stai solo evitando di stampare i proiettili che hanno colpito qualcosa)
                                p_bullet tmp2 = tmp->next;
                                tmp->next = (tmp->next)->next;
                                delete tmp2;
                            }
                        }
                    }
                }
            }
            return h;
        }

        //Funzione che controlla le collisioni proiettili-mappa (AGGIUNGERE CONTROLLO COLLISIONI PROIETTILE NEMICO!!)
        bool check_map_collision_bullet(bool is_left_bullet, int bullet_y, int bullet_x){
            bool noCollision = true;
            if(is_left_bullet){
                if (mapManager->GetCurrentMapList()->GetTail()->GetMap()[bullet_y][bullet_x-2] == WALLCHARACTER)
                    noCollision = false;
            }
            else{
                if (mapManager->GetCurrentMapList()->GetTail()->GetMap()[bullet_y][bullet_x] == WALLCHARACTER)
                    noCollision = false;
            }
            return noCollision;
        }

        //********** Nella seguente sezione viene gestito l'input da tastiera dell'utente **********

        //switch-case per gestire le mosse del personaggio in base al tasto premuto dall'utente
        void getmv(int choice){

            //napms(50);

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
                    if(hit_direction != 2)
                        if (check_map_collision(0))
                            mvleft();
                    if (check_map_collision(3))
                        isFalling = true;
                    //napms(70); //tentativo di non velocizzare tutti i nemici quando si tiene premuta una freccia
                    break;
                case KEY_RIGHT:
                    if(hit_direction != 1)
                        if (check_map_collision(1))
                            mvright();
                    if (check_map_collision(3))
                        isFalling = true;
                    //napms(70); //tentativo di non velocizzare tutti i nemici quando si tiene premuta una freccia
                    break;
                case ' ': //quando si preme la barra spaziatrice
                    isAttacking = true;
                    if(is_left){
                        h = bullet_insert(h, xLoc, yLoc, true);
                    }
                    else{
                        h = bullet_insert(h, xLoc+bound_right-1, yLoc, false);
                    }
                    break;
                default:
                    break;
            }

            if(isJumping){
                jump();
            }
            else if(isFalling){
                fall();
            }

            if(isAttacking){
                h = attack(h);
            }

        }
};