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

        string player_name; //nome del giocatore, che apparirà accanto all'highscore
        int score; //punteggio accumulato durante la partita
        int score_count; //quantità di punteggio mancante prima che aumenti il livello di difficoltà di gioco
        int score_threshold; //score + score_count (soglia di punteggio per aumentare il livello di difficoltà di gioco)
        int level; //livello corrente in cui si trova l'eroe
        int diff_level; //livello di difficoltà di gioco

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

        const char* player_shape_attack_down[2] = {
            "/)'w'(\\",
            "(\")_(\")"
        };

        //costruttore del personaggio
        Hero(WINDOW * win, int y, int x, int bRight, MapManager* map, bool isL, string n, int hp = 400, int st = 15, int df = 1, int r = 2, int m = 0, int s = 0, int lp = 0, bool inv = false, bool dM = false, bool dS = false):Character(win, y, x, bRight, map, isL, hp, st, df, r){
            money = m;
            level = 1;
            diff_level = 0;
            score = s;
            score_count = 100;
            score_threshold = score + score_count;
            luck = lp;
            player_name = n;
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
                                //rimuovo il proiettile dalla lista
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
                               //rimuovo il proiettile dalla lista
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

        //Funzione che controlla le collisioni proiettili-mappa
        bool check_map_collision_bullet(bool is_left_bullet, int bullet_y, int bullet_x){
            bool noCollision = true;
            if(is_left_bullet){
                if (mapManager->GetCurrentMapList()->GetTail()->GetMap()[bullet_y][bullet_x-2] == WALLCHARACTER 
                    || mapManager->GetCurrentMapList()->GetTail()->GetMap()[bullet_y][bullet_x-2] == FLOORCHARACTER)
                    noCollision = false;
            }
            else{
                if (mapManager->GetCurrentMapList()->GetTail()->GetMap()[bullet_y][bullet_x] == WALLCHARACTER
                    || mapManager->GetCurrentMapList()->GetTail()->GetMap()[bullet_y][bullet_x] == FLOORCHARACTER)
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
                if(choice != KEY_DOWN){
                    jump();
                }
                else{
                    isAttackingDown = true;
                    isJumping = false;
                    isFalling = true;
                    fall();
                }
            }
            else if(isFalling){
                fall();
            }

            if(isAttacking){
                h = attack(h);
            }

        }

        //********** Nella seguente sezione si gestiscono l'interazione tra oggetti e eroe **********

        void setStatChange(OggettoMarket o){
            double boost = 1.0 + o.getBoostStat(); //aumento percentuale completo
            //casting a int poichè le statistiche sono valori interi
            if(strcmp(o.getStatAffected(), "health")==0)
                this->setHealth((int)(this->getHealth() *boost)); //Modifica il valore di MAXHP quindi dovrebbe essere setMaxHP...
            else if(strcmp(o.getStatAffected(), "strenght")==0)
                this->setStrenght((int)(this->getStrenght() *boost));
            else if(strcmp(o.getStatAffected(), "defense")==0)
                this->setDefense((int)(this->getDefense() * boost));
            else if(strcmp(o.getStatAffected(), "luck")==0)
                this->setLuck((int)(this->getLuck() * boost));
        }     
        
        const char * purchase(OggettoMarket o){
            if(this->getMoney()>=o.getPrice()){
                this->setMoney(this->getMoney()-(o.getPrice()));
                this->setStatChange(o);
                return "ACQUISTO    AVVENUTO";
            }
            else{
                return "MONETE INSUFFICIENTI";
            }
        }  

        void setStatTemporary(OggettoMappa o){
            if(strcmp(o.getStatAffected(), "invincibility")==0)
                this->setInvincibility(true);
            else if(strcmp(o.getStatAffected(), "doubleMoney")==0)
                this->setDoubleMoney(true);
            else if(strcmp(o.getStatAffected(), "doubleScore")==0)
                this->setDoubleScore(true);
        }

        void setStatPermanent(OggettoMappa o){
            double boost = 1.0 + o.getBoostStat(); //aumento percentuale completo
            //casting a int poichè le statistiche sono valori interi
            if(strcmp(o.getStatAffected(), "health")==0) //Aumenta gli hp di boostStat rispetto ai maxHP
                this->setHealth((int)(this->getHealth() /*+ h.getMaxHp()*/ *boost));
            else if(strcmp(o.getStatAffected(), "strenght")==0)
                this->setStrenght((int)(this->getStrenght() *boost));
            else if(strcmp(o.getStatAffected(), "defense")==0)
                this->setDefense((int)(this->getDefense() * boost));
            else if(strcmp(o.getStatAffected(), "luck")==0)
                this->setLuck((int)(this->getLuck() * boost));
            else if(strcmp(o.getStatAffected(), "jumpForce")==0)
                this->setJumpForce((int)(this->getJumpForce() * boost));  
        } 

        void setStatChange(OggettoMappa o){
            if(o.isTemporary())
                this->setStatTemporary(o);
            //La rimozione dell'effetto viene eseguita quando il personaggio passa al livello successivo
            else if(o.isSpecial()){ //CASO SCONTI
        //Parte di salvataggio su file 
          /* ifstream inputFile; /* Dichiarazione di tipo 
	            char path[100] = "stat.txt"; //file dove vengono salvate le statistiche
                inputFile.open(path);
                string word;
	            if(!inputFile.fail()){
                     while (inputFile >> word) {
                        if(strcmp(word, "Sconti:")==0){ //cerca stringa Sconti
                            inputFile<<"Y"; //Modifica a Y quello dopo
                            break;
                        }
                    }
                }
            }*/
            }
            else
                this->setStatPermanent(o);
        }
};



