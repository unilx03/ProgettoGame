/*----------------------------------------------------------------------------------
Implementazione della superclasse Character ("Personaggio"), classe base di tutta
la gerarchia di classi
----------------------------------------------------------------------------------*/

#include <ncurses/ncurses.h> 

class Character{ 
    private:
        const int JUMP_DELAY = 45; 
        const int JUMP_FORCE = 5; //"forza di salto", ossia numero di righe che costituisce l'altezza del salto
        const char* bullet = "-";

    protected: //protected perché serve che tali attributi siano visibili alle classi che ereditano
        int bound_right;
        int rows; //numero di righe su cui viene disegnato il personaggio
        int xLoc, yLoc, xMax, yMax;                                  
        WINDOW * curwin;
   
    public:
        //NOTA PER ME: aggiungere i seguenti attributi commentati al costruttore ecc.
        //life_points //(per i nemici, dipendono dall'attributo diff_level dell'eroe)

        //la seguente variabile booleana serve per selezionare quale forma del personaggio stampare (quella che "guarda" a sx oppure quella che guarda a dx)
        bool is_left;

        //Costruttore del personaggio. Setta la finestra corrente e la posizione di partenza del personaggio.
        Character(WINDOW * win, int y, int x, int bRight, bool isL = false, int r = 1){
            curwin = win;
            yLoc = y;
            xLoc = x;
            getmaxyx(curwin, yMax, xMax);
            keypad(curwin, true);
            bound_right = bRight;
            is_left = isL;
            rows = r;
        }

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

        //Stampa a video del personaggio, una riga per volta 
        void display(const char* left[], const char* right[]){
            wclear(curwin); //cancella ciò che è stato stampato in precedenza per tenere solo la stampa del personaggio nella sua posizione corrente

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

        //Funzione che fa saltare il personaggio
        void jump(const char* left[], const char* right[]){
            //Controllo innanzitutto se il personaggio è a terra, e solo in quel caso gli permetto di saltare.
            if (yLoc == yMax-(rows+1)) {
                //salto (mantiene la direzione dell'ultima freccia premuta)
                for (int i = 0; i < JUMP_FORCE; i++){
                    yLoc--;
                    if(is_left){
                        mvleft();
                    }
                    else{
                        mvright();
                    }
                    display(left, right);

                    //naps permette di ritardare l'output
                    napms(JUMP_DELAY);
                }
                fall(left, right);
            }
        }

        void fall(const char* left[], const char* right[]){
            //caduta (mantiene la direzione dell'ultima freccia premuta)
            for (int i = 0; i < JUMP_FORCE; i++){
                yLoc++;
                if(is_left){
                    mvleft();
                }
                else{
                    mvright();
                }
                display(left, right);    
                //naps permette di ritardare l'output a video
                napms(JUMP_DELAY);
            }
        }

        //funzione di attacco (permette al personaggio di "sparare proiettili")
        void attack(const char* left[], const char* right[]){
            if(is_left){
                for(int i = xLoc -1 ; i > 1; i--){
                    //display(left, right);
                    napms(40);
                    mvwprintw(curwin, yLoc, xLoc+i, bullet);
                }
            }
            else{
                for(int i = xLoc + bound_right; i < xMax; i++){
                    //display(left, right);
                    napms(40);
                    mvwprintw(curwin, yLoc, xLoc+i, bullet);
                }
            }
        }

};

