#include <ctime>        // std::time
#include <cstdlib>      // std::rand, std::srand
#include "OggettoMappa.h"


OggettoMappa* getItemDrop(int i, OggettoMappa* item[]);
//Dato un indice ritorna l'oggetto corrispondente

OggettoMappa* chosenObject(OggettoMappa* item[], bool lucky);
//Ritorna l'indice dell'oggetto scelto in base alle probabilità
