#include "OggettoMarket.h"

class Market{
    protected:
    OggettoMarket * item[N];

    public:
        Market(){
            item[0] = new OggettoMarket ("Carota Vita","--", 0.05,"health",55.8);
            item[1] = new OggettoMarket("Carota Forza", "++", 0.03,"strenght",44.3);
            item[2] = new OggettoMarket("Carota Veloce", "..", 0.01,"attackSpeed",22.0);
            item[3] = new OggettoMarket("Carota Difesa", ",,", 0.05,"defense",11.11);
            item[4] = new OggettoMarket("Carota Fortuna", "__", 0.01,"luck",100.99);
        }

        OggettoMarket * getItem(int i);
};
