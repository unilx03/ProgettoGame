#include <ctime>        // std::time
#include <cstdlib>      // std::rand, std::srand
#include "OggettoMappa.h"
/*
OggettoMappa* item[M];
            item[0] = new OggettoMappa("Healing Carrot", "<3", 0.2, "health");
            item[1] = new OggettoMappa("Carrot Sword", "=>", 0.1, "strenght");
            item[2] = new OggettoMappa("Carrot Shield", "|)", 0.1, "defense");
            item[3] = new OggettoMappa("Greedy Carrot", "$$", 0.5, "doubleMoney", true);
            item[4] = new OggettoMappa("Carrot Points", "##", 0.5, "doubleScore", true);
            item[5] = new OggettoMappa("Magic Carrot", "|3", 1.0, "invincibility", true);
            item[6] = new OggettoMappa("Bouncing Carrot", "|7", 0.05, "jumpForce");
            item[7] = new OggettoMappa("Sale", "££", 0.2, "sale", false, true);
*/

OggettoMappa* getItemDrop(int i, OggettoMappa* item[]);
//Dato un indice ritorna l'oggetto corrispondente

OggettoMappa* chosenObject(OggettoMappa* item[]);
//Ritorna l'indice dell'oggetto scelto in base alle probabilità
