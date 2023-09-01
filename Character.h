/*----------------------------------------------------------------------------------
Implementazione della superclasse Character ("Personaggio"), classe base di tutta
la gerarchia di classi
----------------------------------------------------------------------------------*/

#include <ncurses/ncurses.h>

#include "MapManager.h"

class Character{ 
    private:
        //attributi su cui avranno influenza gli oggetti
        int health; //punti vita
        int strenght; //quantità di danno inflitto
        int defense; //punti difesa
   
    public:

        WINDOW * curwin;

        int jumpForce; //"forza di salto", ossia numero di righe che costituisce l'altezza del salto
        bool isJumping;
        int jumpCounter;
        bool isFalling;
        bool isAttackingDown; //è vero quando si sta eseguendo un attacco dall'alto verso il basso

        int bound_right;
        int rows; //numero di righe su cui viene disegnato il personaggio
        int xLoc, yLoc, xMax, yMax;  
        bool is_hit; //true se un entità è stata colpita
        int hit_direction; //DA DOVE è arrivato il colpo. Nessun colpo = 0, dx = 1, sx = 2, down = 3, up = 4

        //la seguente variabile booleana serve per selezionare quale forma del personaggio stampare (quella che "guarda" a sx oppure quella che "guarda" a dx)
        bool is_left;
        MapManager* mapManager;

        void setJumpForce(int n){
            jumpForce = n;
        }
        int getJumpForce(){
            return jumpForce;
        }
        void setHealth(int n){
            health = n;
        }
        int getHealth(){
            return health;
        }
        void setStrenght(int n){
            strenght = n;
        }
        int getStrenght(){
            return strenght;
        }
        void setDefense(int n){
            defense = n;
        }
        int getDefense(){
            return defense;
        }

        //Costruttore del personaggio. Setta la finestra corrente e la posizione di partenza del personaggio.
        Character(WINDOW * win, int y, int x, int bRight, MapManager* map, bool isL, int hp = 50, int st = 5, int df = 0, int r = 1, int jF = 5){
            curwin = win;
            yLoc = y;
            xLoc = x;
            getmaxyx(curwin, yMax, xMax);
            bound_right = bRight;
            is_left = isL;
            rows = r;
            jumpForce = jF;
            health = hp;
            strenght = st;
            defense = df;

            is_hit = false;
            hit_direction = 0;

            mapManager = map;
            isJumping = false;
            jumpCounter = 0;
            isFalling = false;
            isAttackingDown = false;
        }
        void display(const char* left[], const char* right[]);
        void mvleft();
        void mvright();
        void jump();
        void fall();
        bool check_map_collision(int direction);
};

