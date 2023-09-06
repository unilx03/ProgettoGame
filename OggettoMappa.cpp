#include "OggettoMappa.h"

const char * OggettoMappa::getSkin(){
    return skin;
}

bool OggettoMappa::isTemporary(){
    return temporary;
}

bool OggettoMappa::isSpecial(){
    return special;
}

double OggettoMappa::getBoostStat(){
    return boostStat;
}
void OggettoMappa::setBoostStat(double boostStat){
    this -> boostStat = boostStat;
}

void OggettoMappa::setStatAffected(const char * statAffected){
    this -> statAffected = statAffected;
}
const char * OggettoMappa::getStatAffected(){
    return statAffected;
}

int OggettoMappa::getXOgg(){
    return xOgg;
}
void OggettoMappa::setXOgg(int xOgg){
    this -> xOgg = xOgg;
}

int OggettoMappa::getYOgg(){
    return yOgg;
}
void OggettoMappa::setYOgg(int yOgg){
    this -> yOgg = yOgg;
}

const char * OggettoMappa::getName(){
    return name;
}

bool OggettoMappa::getTemporary(){
    return temporary;
}

bool OggettoMappa::getSpecial(){
    return special;
}