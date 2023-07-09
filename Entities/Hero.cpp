/*----------------------------------------------------------------------------------
Utilizzo della classe Hero (definita in Hero.h) per la creazione e la gestione 
delle azioni dell'eroe
----------------------------------------------------------------------------------*/

#include <ncurses.h>
#include "Hero.h"

void create_hero(WINDOW * playwin, int y, int x){
    char name[7] = "Ettore"; //nome di default del personaggino

    //creazione del personaggio
    Hero * c = new Hero(playwin, y, x, 8, name);
    
    //loop per muovere il personaggio all'interno della window
    do{
        c->display(c->player_shape_left, c->player_shape_right);
    }while(c->getmv()!='x'); //chiusura del gioco quando si preme il tasto x
}