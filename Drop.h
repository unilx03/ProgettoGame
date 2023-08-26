#include "OggettoMappa.h"

class Drop{
    protected:
        OggettoMappa* item[M];
    
    public:
        Drop(){
            item[0] = new OggettoMappa("Healing Carrot", "<3", 0.2, "health", 0.3);
            item[1] = new OggettoMappa("Carrot Sword", "=>", 0.1, "strenght", 0.15);
            item[2] = new OggettoMappa("Carrot Shield", "|)", 0.1, "defense", 0.15);
            item[3] = new OggettoMappa("Greedy Carrot", "$$", 0.5, "doubleMoney", 0.1, true);
            item[4] = new OggettoMappa("Carrot Points", "##", 0.5, "doubleScore", 0.1, true);
            item[5] = new OggettoMappa("Magic Carrot", "|3", 1.0, "invincibility", 0.8, true);
            item[6] = new OggettoMappa("Bouncing Carrot", "|7", 0.05, "jumpForce", 0.05);
            item[7] = new OggettoMappa("Speedy Carrot", "?!", 0.1, "attackSpeed", 0.05);
            item[8] = new OggettoMappa("Sale", "££", 0.2, "sale", 0.02, false, true);
        }
        //Riempie il vettore con i 8 oggetti droppabili durante la run

        OggettoMappa* getItemDrop(int i);
        //Dato un indice ritorna l'oggetto corrispondente
};