/*----------------------------------------------------------------------------------
Implementazione della superclasse Character ("Personaggio"), classe base di tutta
la gerarchia di classi
----------------------------------------------------------------------------------*/

#include <ncurses.h>

#include "MapManager.h"

class Character{ 
    private:
        const int JUMP_DELAY = 45; 
        const char* bullet = "-";

        //attributi su cui avranno influenza gli oggetti
        int attackSpeed; //velocità con cui vengono sparati i proiettili
        int health; //punti vita
        int strenght; //quantità di danno inflitto
        int defense; //punti difesa

    protected: //protected perché serve che tali attributi siano visibili alle classi che ereditano
        int bound_right;
        int rows; //numero di righe su cui viene disegnato il personaggio
        int xLoc, yLoc, xMax, yMax;   

        WINDOW * curwin;

        int jumpForce; //"forza di salto", ossia numero di righe che costituisce l'altezza del salto
        bool isJumping;
        int jumpCounter;
        bool isFalling;
   
    public:
        //la seguente variabile booleana serve per selezionare quale forma del personaggio stampare (quella che "guarda" a sx oppure quella che "guarda" a dx)
        bool is_left;
        MapManager* mapManager;

        void setJumpForce(int n){
            jumpForce = n;
        }
        int getJumpForce(){
            return jumpForce;
        }
        void setAttacckSpeed(int n){
            attackSpeed = n;
        }
        int getAttackSpeed(){
            return attackSpeed;
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
        int geDefence(){
            return defense;
        }


        //Costruttore del personaggio. Setta la finestra corrente e la posizione di partenza del personaggio.
        //NOTA PER ME: i punti vita (attributo health) andranno modificati nei costruttori di ogni tipo di personaggio/nemico
        Character(WINDOW * win, int y, int x, int bRight, MapManager* map, int hp = 5, int st = 3, int df = 1, bool isL = false, int r = 1, int jF = 4, int aS = 20){
            curwin = win;
            yLoc = y;
            xLoc = x;
            //getmaxyx(curwin, yMax, xMax);
            //keypad(curwin, true);
            bound_right = bRight;
            is_left = isL;
            rows = r;
            jumpForce = jF;
            attackSpeed = aS;
            health = hp;
            strenght = st;
            defense = df;

            mapManager = map;
            isJumping = false;
            jumpCounter = 0;
            isFalling = false;
        }

        //Spostamento a sinistra del personaggino
        void mvleft(){
            //da aggiungere: richiamare funzione di caduta se arriva alla fine di una piattaforma elevata
            is_left = true;
            xLoc--;
            if(xLoc < 1){
                xLoc = 1; //la costante 1 è necessario per non far fuoriuscire il personaggio dai bordi della box
                is_left = false;
            }
        }

        //Spostamento a destra del personaggino
        void mvright(){
            //da aggiungere: richiamare funzione di caduta se arriva alla fine di una piattaforma elevata
            is_left = false;
            xLoc++;
            if(xLoc > xMax-bound_right){
                xLoc = xMax-bound_right; //la costante bound_right è necessaria per non far fuoriuscire il personaggio dai bordi della box
                is_left = true;
            }
        }

        //Stampa a video del personaggio, una riga per volta 
        void display(const char* left[], const char* right[]){
            //wclear(curwin); //cancella ciò che è stato stampato in precedenza per tenere solo la stampa del personaggio nella sua posizione corrente

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

        //Funzione che fa saltare il personaggio a dx e a sx
        void jump(const char* left[], const char* right[]){
            //da aggiungere: gestione dei salti sulle/dalle piattaforme
            //Controllo innanzitutto se il personaggio è a terra, e solo in quel caso gli permetto di saltare.
            if (yLoc == yMax-(rows+1)) {
                //salto (mantiene la direzione dell'ultima freccia premuta)
                for (int i = 0; i < jumpForce; i++){
                    yLoc--;
                    if(is_left){
                        mvleft();
                    }
                    else{
                        mvright();
                    }
                    display(left, right);

                    //naps permette di ritardare l'output
                    //napms(JUMP_DELAY);
                    //wtimeout(win, 100);
                }
            }
        }

        //Funzione che fa cadere il personaggio
        void fall(const char* left[], const char* right[]){
            //caduta (mantiene la direzione dell'ultima freccia premuta)
            for (int i = 0; i < jumpForce; i++){
                yLoc++;
                if(is_left){
                    mvleft();
                }
                else{
                    mvright();
                }
                display(left, right);    
                //naps permette di ritardare l'output a video
                //napms(JUMP_DELAY);
            }
        }

        //Funzione che fa saltare il personaggio in verticale
        void jump_vertical(const char* left[], const char* right[]){
            /*
            //da aggiungere: gestione interazione con piattaforme
            //Controllo innanzitutto se il personaggio è a terra, e solo in quel caso gli permetto di saltare.
            if (yLoc == yMax-(rows+1)) {
                //salto
                for (int i = 0; i < jumpForce; i++){
                    yLoc--;
                    display(left, right);
                    napms(JUMP_DELAY);
                }
            } */
         
            if (isJumping)
            {
                bool stillJumping = true;
                if (jumpCounter > 0)
                {
                    jumpCounter--;
                    if (check_map_collision(2))
                    {
                        yLoc--;
                        //display(left, right);
                    }
                    else
                        stillJumping = false;
                    //napms(JUMP_DELAY);
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

        void fall_vertical(const char* left[], const char* right[]){
            /*
            //caduta
            for (int i = 0; i < jumpForce; i++){
                yLoc++;
                display(left, right);    
                napms(JUMP_DELAY);
            }
            */
            
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
                //napms(JUMP_DELAY);
            }
        }

        //Funzione che fa cadere il personaggio in verticale

        //Funzione che stampa il poiettile che viene sparato con la funzione attack()
        void attack_display(const char* left[], const char* right[], int i){
            display(left, right);
            mvwprintw(curwin, yLoc, i, bullet);
            wrefresh(curwin);
            napms(attackSpeed);
        }

        //Funzione di attacco (permette al personaggio di "sparare proiettili")
        void attack(const char* left[], const char* right[]){
            if(is_left){
                for(int i = xLoc -1 ; i > 1; i--){
                    attack_display(left, right, i);
                }
            }
            else{
                for(int i = xLoc+bound_right-1; i < xMax-1; i++){
                   attack_display(left, right, i);
                }
            }
        }

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
