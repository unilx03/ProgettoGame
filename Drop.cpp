#include "Drop.h"
OggettoMappa* getItemDrop(int i, OggettoMappa* item[]){
    return item[i];
}

OggettoMappa* chosenObject(OggettoMappa* item[], bool lucky){
    int num = rand()%100;
    int index = 0;
    if(!lucky){ //probabilità caso base
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
                index = 7;
                break;
            default:
                break;
        }
    }
    else{ //Probabilità caso fortunato (FortunePoints>0)
        switch (num){
            case 0 ... 24: //Healing carrot 20%
                index = 0;
                break;
            case 25 ... 34: //Carrot sword 10%
                index = 1;
                break;
            case 35 ... 39: //Carrot shield 5%
                index = 2;
                break;
            case 40 ... 54: //Greedy carrot 15%
                index = 3;
                break;
            case 55 ... 69: //Carrot points 15% 
                index = 4;
                break;
            case 70 ... 84: //Magic carrot 15%%
                index = 5;
                break;
            case 85 ... 94: //Bouncing carrot 10%
                index = 6;
                break;
            case 95 ... 99: //Sale 5%
                index = 7;
                break;
            default:
                break;
        }     
    }
    return item[index];
}