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
        int maxHp;

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
        bool has_found_obj;

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
        void setMaxHp(int n){
            maxHp = n;
        }
        int getMaxHp(){
            return maxHp;
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
        
        const char* player_shape_right_obj[2] = {
            "  (\\ /)",
            "( =^O^)"
        };
        const char* player_shape_left_obj[2] = {
            "(\\ /) ",
            "(^O^= )"
        };

        //costruttore del personaggio
        Hero(WINDOW * win, int y, int x, int bRight, MapManager* map, bool isL, string n, int hp = 600, int st = 15, int df = 1, int r = 2, int m = 0, int s = 0, int lp = 0, bool inv = false, bool dM = false, bool dS = false):Character(win, y, x, bRight, map, isL, hp, st, df, r){
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
            maxHp = hp;
            has_found_obj = false;
        }
        p_bullet bullet_insert(p_bullet h, int x, int y, bool left);
        p_bullet attack(p_bullet h);
        bool check_map_collision_bullet(bool is_left_bullet, int bullet_y, int bullet_x);
        void getmv(int choice);

        void setStatChange(OggettoMarket o);
        const char * purchase(OggettoMarket o);
        void setStatTemporary(OggettoMappa o);
        void setStatPermanent(OggettoMappa o);
        void setStatChange(OggettoMappa o);
        
        void hero_object_collision(OggettoMappa o);
};



