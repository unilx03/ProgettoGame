#include "FlyingEnemyX.h"

//Spostamento in su del nemico
void FlyingEnemyX::mvup(){
    this->is_up = true;
    this->yLoc--;
}

//Spostamento in giù del nemico
void FlyingEnemyX::mvdown(){
    this->is_up = false;
    this->yLoc++;
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

//Funzione che controlla le collisioni entità-mappa
bool FlyingEnemyX::check_map_collision(int direction) {
    bool noCollision = true;
    int checkY = 0;
    switch (direction){
        case 2: //top
            if ((this->yLoc) - 2 < 0)  //(yLoc - rows + 1) limite superiore effettivo
                noCollision = false;
            else if (mapManager->GetCurrentMapList()->GetTail()->GetMap()[(this->yLoc) - 2][this->xLoc - 1] == FLOORCHARACTER ||
                mapManager->GetCurrentMapList()->GetTail()->GetMap()[(this->yLoc) - 2][(this->xLoc + this->bound_right - 1) - 1] == FLOORCHARACTER)
                noCollision = false;
            break;

        case 3: //bottom
            if (this->yLoc + this->rows > ROW)
                noCollision = false;
            else if (mapManager->GetCurrentMapList()->GetTail()->GetMap()[this->yLoc + this->rows -1][this->xLoc - 1] == FLOORCHARACTER ||
                mapManager->GetCurrentMapList()->GetTail()->GetMap()[this->yLoc + this->rows -1][(this->xLoc + this->bound_right - 1) - 1] == FLOORCHARACTER)
                noCollision = false;
            break;

        default:
            noCollision = false;
            break;
    }
    return noCollision;
}