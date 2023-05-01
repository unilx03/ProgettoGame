#include "Market.h"

void Market::initializeMarket(){
    //name, skin, boostStat, statAffected, price
    item[0] = OggettoMarket ("Carota Vita","--", 0.05,"health",55.8);
    item[1] = OggettoMarket("Carota Forza", "++", 0.03,"strenght",44.3);
    item[2] = OggettoMarket("Carota Veloce", "..", 0.01,"attackSpeed",22.0);
    item[3] = OggettoMarket("Carota Difesa", ",,", 0.05,"defense",11.11);
    item[4] = OggettoMarket("Carota Fortuna", "__", 0.01,"luck",100.99);
}   

OggettoMarket Market::getItem(int i){
    return item[i];
}