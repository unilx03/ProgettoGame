#include "OggettoMarket.h"

class Market{
    protected:
    OggettoMarket * item[N];

    public:
        Market(){
            item[0] = new OggettoMarket ("BISCOTTO VITA","<3", 0.05,"health",55);
            item[1] = new OggettoMarket("SPINACI", "YY", 0.03,"strenght",44);
            item[2] = new OggettoMarket("POZIONE SALTO", "()", 0.02,"JumpForce",22);
            item[3] = new OggettoMarket("SCUDO CAROTA", "][", 0.05,"defense",11);
            item[4] = new OggettoMarket("CAROTA FORTUNA", "X>", 0.01,"luck",100);
        }

        OggettoMarket * getItem(int i);
};
