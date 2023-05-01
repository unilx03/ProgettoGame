#include "Drop.h"

void Drop::initializeDrop(){
    //name, skin, boostStat, statAffected, probability, temporary = false, special = false
    item[0] = OggettoMappa("Healing Carrot", "E>", 0.2, "health", 0.3);
    item[1] = OggettoMappa("Carrot Sword", "=>", 0.1, "strenght", 0.15);
    item[2] = OggettoMappa("Carrot Shield", "||", 0.1, "defense", 0.15);
    item[3] = OggettoMappa("Greedy Carrot", "$$", 0.5, "doubleMoney", 0.1, true);
    item[4] = OggettoMappa("Carrot Points", "##", 0.5, "doubleScore", 0.1, true);
    item[5] = OggettoMappa("Magic Carrot", "3>", 1.0, "invincibility", 0.8, true);
    item[6] = OggettoMappa("Bouncing Carrot", ":.", 0.05, "jumpForce", 0.05);
    item[7] = OggettoMappa("Speedy Carrot", "((", 0.1, "attackSpeed", 0.05);
    item[8] = OggettoMappa("Sale", "££", 0.2, "sale", 0.02, false, true);
}

OggettoMappa Drop::getItem(int i){
    return item[i];
}