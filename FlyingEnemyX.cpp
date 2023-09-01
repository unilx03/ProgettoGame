#include "FlyingEnemyX.h"

//Spostamento in su del nemico
void FlyingEnemyX::mvup(){
    this->is_up = true;
    this->yLoc--;
    if(this->yLoc < 1){
        this->yLoc = 1;
        this->is_up = false;
    }
}

//Spostamento in giù del nemico
void FlyingEnemyX::mvdown(){
    this->is_up = false;
    this->yLoc++;
    if(this->yLoc > this->yMax-(this->rows+1)){
        this->yLoc = this->yMax-(this->rows+1);
        this->is_up = true;
    }
}

//funzione che fa muovere il nemico su e giù
void FlyingEnemyX::mv_up_down(){
    if(this->is_up){
        if(check_map_collision(2))
            mvup();
        else
            this->is_up = false;
    }
    else{
        if(check_map_collision(3))
            mvdown();
        else
            this->is_up = true;
    }
 }