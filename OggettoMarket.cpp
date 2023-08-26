#include "OggettoMarket.h"

const char * OggettoMarket::getSkin(){
    return skin;
}

int OggettoMarket::getPrice(){
    return price;
}
void OggettoMarket::setPrice(int price){
    this->price = price;
}

double OggettoMarket::getBoostStat(){
    return boostStat;
}
void OggettoMarket::setBoostStat(double boostStat){
    this -> boostStat = boostStat;
}

void OggettoMarket::setStatAffected(const char * statAffected){
    this -> statAffected = statAffected;
}
const char * OggettoMarket::getStatAffected(){
    return statAffected;
}