#include "Character.h"

//Stampa a video del personaggio, una riga per volta 
void Character::display(const char* left[], const char* right[]){
    if(this->is_left){
        for (int i = 0; i < this->rows; i++) {
            mvwprintw(this->curwin, this->yLoc + i, this->xLoc, left[i]);
        }
    }
    else{
        for (int i = 0; i < this->rows; i++) {
            mvwprintw(this->curwin, this->yLoc + i, this->xLoc, right[i]);
        }
    }

    //le righe seguenti ricreano la cornice della box ad ogni movimento del personaggio (necessario!)
    box(this->curwin, 0, 0);
    wrefresh(curwin);
}

//********** Nella seguente sezione si gestiscono i movimenti **********

//Spostamento a sinistra del personaggino
void Character::mvleft(){
    this->is_left = true;
    this->xLoc--;
    if(this->xLoc < 1){
                this->xLoc = 1; //la costante 1 è necessario per non far fuoriuscire il personaggio dai bordi della box
                this->is_left = false;
    }
}

//Spostamento a destra del personaggino
void Character::mvright(){
    this->is_left = false;
    this->xLoc++;
    if(this->xLoc > this->xMax-this->bound_right){
        this->xLoc = this->xMax-this->bound_right; //la costante bound_right è necessaria per non far fuoriuscire il personaggio dai bordi della box
        this->is_left = true;
    }
}

//Funzione che fa saltare il personaggio
void Character::jump(){   
    if(this->is_left && check_map_collision(0))
        mvleft();
    else if (!(this->is_left) && check_map_collision(1))
        mvright();

    if (this->isJumping){
        bool stillJumping = true;
        if (this->jumpCounter > 0){
            this->jumpCounter--;
            if (check_map_collision(2)){
                this->yLoc--;
            }
            else
                stillJumping = false;
        }
        else
            stillJumping = false;
                
        if(!stillJumping){
            this->isJumping = false;
            this->jumpCounter = 0;
            if(check_map_collision(3)){
                this->isFalling = true;
            }
            else{
                this->isFalling = false;
            }
        }
    }
}

//Funzione che fa cadere il personaggio
void Character::fall(){
    if(this->isFalling){
        if(check_map_collision(3)){
            this->yLoc++;
        }
        else{
            this->isFalling = false;
            this->isAttackingDown = false;
        }
    }
}

//Funzione che controlla le collisioni entità-mappa
bool Character::check_map_collision(int direction) {
    bool noCollision = true;
    int checkY = 0;
    switch (direction){
        case 0: //left
            checkY = 0;
            while (checkY < this->rows){
                if(mapManager->GetCurrentMapList()->GetTail()->GetMap()[this->yLoc - checkY][this->xLoc - 2] == WALLCHARACTER ||
                    mapManager->GetCurrentMapList()->GetTail()->GetMap()[this->yLoc - checkY][this->xLoc - 2] == FLOORCHARACTER)
                    noCollision = false;
                checkY++;
            }
            break;
                    
        case 1: //right     (xLoc + bound_right - 1) limite a destra effettivo 
            checkY = 0;
            while (checkY < this->rows){
                if (mapManager->GetCurrentMapList()->GetTail()->GetMap()[this->yLoc - checkY][(this->xLoc + this->bound_right - 1)] == WALLCHARACTER ||
                    mapManager->GetCurrentMapList()->GetTail()->GetMap()[this->yLoc - checkY][(this->xLoc + this->bound_right - 1)] == FLOORCHARACTER)
                    noCollision = false;
                checkY++;
            }
            break;

        case 2: //top
            if ((this->yLoc - this->rows + 1) - 1 < 0)  //(yLoc - rows + 1) limite superiore effettivo
                noCollision = false;
            else if (mapManager->GetCurrentMapList()->GetTail()->GetMap()[(this->yLoc - rows + 1) - 1][this->xLoc - 1] == FLOORCHARACTER ||
                mapManager->GetCurrentMapList()->GetTail()->GetMap()[(this->yLoc - rows + 1) - 1][(this->xLoc + this->bound_right - 1) - 1] == FLOORCHARACTER)
                noCollision = false;
            break;

        case 3: //bottom
            if (this->yLoc + 1 > ROW - 1)
                noCollision = false;
            else if (mapManager->GetCurrentMapList()->GetTail()->GetMap()[this->yLoc + 1][this->xLoc - 1] == FLOORCHARACTER ||
                mapManager->GetCurrentMapList()->GetTail()->GetMap()[this->yLoc + 1][(this->xLoc + this->bound_right - 1) - 1] == FLOORCHARACTER)
                noCollision = false;
            break;

        default:
            noCollision = false;
            break;
    }

    //cout << "No Collision " << noCollision << endl;
    return noCollision;
}