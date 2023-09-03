#include "Drop.h"
OggettoMappa* getItemDrop(int i, OggettoMappa* item[]){
    return item[i];
}

OggettoMappa* chosenObject(OggettoMappa* item[]){
    int num = rand()%100;
    int index = 0;
    switch (num){
        case 0 ... 39: //Healing carrot 40%
            index = 0;
            break;
        case 40 ... 54: //Carrot sword 15%
            index = 1;
            break;
        case 55 ... 69: //Carrot shield 15%
            index = 2;
            break;
        case 70 ... 81: //Greedy carrot 12%
            index = 3;
            break;
        case 82 ... 93: //Carrot points 12%
            index = 4;
            break;
        case 94 ... 96: //Magic carrot 3%
            index = 5;
            break;
        case 97 ... 98: //Bouncing carrot 2%
            index = 6;
            break;
        case 99: //Sale 1%
            index = 8;
            break;
        default:
            break;
    }
    return item[index];
}