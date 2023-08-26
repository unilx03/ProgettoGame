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
        //NOTA PER ME: i punti vita (attributo health) andranno modificati nei costruttori di ogni tipo di personaggio/nemico
        Character(WINDOW * win, int y, int x, int bRight, MapManager* map, bool isL, int hp = 5, int st = 3, int df = 1, int r = 1, int jF = 5){
            curwin = win;
            yLoc = y;
            xLoc = x;
            getmaxyx(curwin, yMax, xMax);
            //keypad(curwin, true);
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
        }

        //Stampa a video del personaggio, una riga per volta 
        void display(const char* left[], const char* right[]){
            if(is_left){
                for (int i = 0; i < rows; i++) {
                    mvwprintw(curwin, yLoc + i, xLoc, left[i]);
                }
            }
            else{
                for (int i = 0; i < rows; i++) {
                    mvwprintw(curwin, yLoc + i, xLoc, right[i]);
                }
            }

            //le righe seguenti ricreano la cornice della box ad ogni movimento del personaggio (necessario!)
            box(curwin, 0, 0);
            wrefresh(curwin);
        }

        //********** Nella seguente sezione si gestiscono i movimenti **********

        //Spostamento a sinistra del personaggino
        void mvleft(){
            is_left = true;
            xLoc--;
            if(xLoc < 1){
                xLoc = 1; //la costante 1 è necessario per non far fuoriuscire il personaggio dai bordi della box
                is_left = false;
            }
        }

        //Spostamento a destra del personaggino
        void mvright(){
            is_left = false;
            xLoc++;
            if(xLoc > xMax-bound_right){
                xLoc = xMax-bound_right; //la costante bound_right è necessaria per non far fuoriuscire il personaggio dai bordi della box
                is_left = true;
            }
        }

        //Funzione che fa saltare il personaggio
        void jump(){
            if (isJumping)
            {
                bool stillJumping = true;
                if (jumpCounter > 0)
                {
                    jumpCounter--;
                    if (check_map_collision(2))
                    {
                        yLoc--;
                    }
                    else
                        stillJumping = false;
                }
                else
                    stillJumping = false;
                
                if (!stillJumping)
                {
                    isJumping = false;
                    jumpCounter = 0;
                    if (check_map_collision(3))
                    {
                        isFalling = true;
                    }
                    else
                    {
                        isFalling = false;
                    }
                }
            }
        }

        //Funzione che fa cadere il personaggio
        void fall(){
            if (isFalling)
            {
                if (check_map_collision(3))
                {
                    yLoc++;
                    //display(left, right);
                }
                else
                {
                    isFalling = false;
                }
            }
        }

        //Funzione che controlla le collisioni entità-mappa
        bool check_map_collision(int direction) 
        {
            bool noCollision = true;
            int checkY = 0;
            switch (direction)
            {
                case 0: //left
                    checkY = 0;
                    while (checkY < rows)
                    {
                        if (mapManager->GetCurrentMapList()->GetTail()->GetMap()[yLoc - checkY][xLoc - 2] == WALLCHARACTER ||
                            mapManager->GetCurrentMapList()->GetTail()->GetMap()[yLoc - checkY][xLoc - 2] == FLOORCHARACTER)
                            noCollision = false;
                        checkY++;
                    }
                    break;
                    
                case 1: //right     (xLoc + bound_right - 1) limite a destra effettivo 
                    checkY = 0;
                    while (checkY < rows)
                    {
                        if (mapManager->GetCurrentMapList()->GetTail()->GetMap()[yLoc - checkY][(xLoc + bound_right - 1)] == WALLCHARACTER ||
                            mapManager->GetCurrentMapList()->GetTail()->GetMap()[yLoc - checkY][(xLoc + bound_right - 1)] == FLOORCHARACTER)
                            noCollision = false;
                        checkY++;
                    }
                    break;

                case 2: //top
                    if ((yLoc - rows + 1) - 1 < 0)  //(yLoc - rows + 1) limite superiore effettivo
                        noCollision = false;
                    else if (mapManager->GetCurrentMapList()->GetTail()->GetMap()[(yLoc - rows + 1) - 1][xLoc - 1] == FLOORCHARACTER ||
                        mapManager->GetCurrentMapList()->GetTail()->GetMap()[(yLoc - rows + 1) - 1][(xLoc + bound_right - 1) - 1] == FLOORCHARACTER)
                        noCollision = false;
                    break;

                case 3: //bottom
                    if (yLoc + 1 > ROW - 1)
                        noCollision = false;
                    else if (mapManager->GetCurrentMapList()->GetTail()->GetMap()[yLoc + 1][xLoc - 1] == FLOORCHARACTER ||
                        mapManager->GetCurrentMapList()->GetTail()->GetMap()[yLoc + 1][(xLoc + bound_right - 1) - 1] == FLOORCHARACTER)
                        noCollision = false;
                    break;

                default:
                    noCollision = false;
                    break;
            }

            //cout << "No Collision " << noCollision << endl;
            return noCollision;
        }
       
};

