#include "OggettoMappa.h"

class Drop{
    protected:
        OggettoMappa item[M];
    
    public:
        void initializeDrop();
        //Riempie il vettore con i 8 oggetti droppabili durante la run

        OggettoMappa getItem(int i);
        //Dato un indice ritorna l'oggetto corrispondente
};