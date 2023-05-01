#include "OggettoMarket.h"

class Market{
    protected:
        OggettoMarket item[N];
    public:
        void initializeMarket();
        //Riempie il vettore con i 5 oggetti del market
        
        OggettoMarket getItem(int i);
        //Dato un indice ritorna l'oggetto corrispondente
};