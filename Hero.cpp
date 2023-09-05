#include "Hero.h"

//********** Nella seguente sezione si gestisce l'attacco con i proiettili **********

//Funzione che inserisce un nuovo proiettile in testa alla lista
Hero::p_bullet Hero::bullet_insert(Hero::p_bullet h, int x, int y, bool left){
    p_bullet tmp = new bulletNode;
    tmp->bullet_x = x;
    tmp->bullet_y = y;
    tmp->is_left_bullet = left;
    tmp->next = h;
    return tmp;
}

//Funzione di attacco (permette al personaggio di "sparare proiettili")
Hero::p_bullet Hero::attack(Hero::p_bullet h){
    if(this->isAttacking){
        if(h == NULL) //controllo se ci sono ancora proiettili nella lista
            this->isAttacking = false;
        else{
            //check del primo elemento
            if(h->is_left_bullet){
                if(h->bullet_x > 1 && check_map_collision_bullet(h->is_left_bullet, h->bullet_y, h->bullet_x)){
                    h->bullet_x--;
                    mvwprintw(curwin, h->bullet_y, h->bullet_x, this->bullet);
                }
                else{
                    //rimuovo il proiettile dalla lista                                
                    Hero::p_bullet h2 = h;
                    h = h->next;
                    delete(h2);
                }
            }
            else{
                if(h->bullet_x < this->xMax-1 && check_map_collision_bullet(h->is_left_bullet, h->bullet_y, h->bullet_x)){
                    h->bullet_x++;
                    mvwprintw(this->curwin, h->bullet_y, h->bullet_x, this->bullet);
                }
                else{
                    //rimuovo il proiettile dalla lista
                    Hero::p_bullet h2 = h;
                    h = h->next;
                    delete(h2);
                }
            }

            //check dal secondo elemento in poi
            Hero::p_bullet tmp = h;
            while(tmp!=NULL && (tmp->next)!=NULL){
                if((tmp->next)->is_left_bullet){
                    if((tmp->next)->bullet_x > 1 && check_map_collision_bullet((tmp->next)->is_left_bullet, (tmp->next)->bullet_y, (tmp->next)->bullet_x)){
                        (tmp->next)->bullet_x--;
                        mvwprintw(this->curwin, (tmp->next)->bullet_y, (tmp->next)->bullet_x, this->bullet);
                        tmp = tmp->next;
                    }
                    else{
                        //rimuovo il proiettile dalla lista
                        Hero::p_bullet tmp2 = tmp->next;
                        tmp->next = (tmp->next)->next;
                        delete tmp2;
                    }
                }
                else{
                    if((tmp->next)->bullet_x < this->xMax-1 && check_map_collision_bullet((tmp->next)->is_left_bullet, (tmp->next)->bullet_y, (tmp->next)->bullet_x)){
                        (tmp->next)->bullet_x++;
                        mvwprintw(this->curwin, (tmp->next)->bullet_y, (tmp->next)->bullet_x, this->bullet);
                        tmp = tmp->next;
                    }
                    else{
                        //rimuovo il proiettile dalla lista
                        Hero::p_bullet tmp2 = tmp->next;
                        tmp->next = (tmp->next)->next;
                        delete tmp2;
                    }
                }
            }
        }
    }
    return h;
}

//Funzione che controlla le collisioni proiettili-mappa
bool Hero::check_map_collision_bullet(bool is_left_bullet, int bullet_y, int bullet_x){
    bool noCollision = true;
    if(is_left_bullet){
        if (mapManager->GetCurrentMapList()->GetTail()->GetMap()[bullet_y][bullet_x-2] == WALLCHARACTER 
            || mapManager->GetCurrentMapList()->GetTail()->GetMap()[bullet_y][bullet_x-2] == FLOORCHARACTER)
            noCollision = false;
    }
    else{
        if(mapManager->GetCurrentMapList()->GetTail()->GetMap()[bullet_y][bullet_x] == WALLCHARACTER
            || mapManager->GetCurrentMapList()->GetTail()->GetMap()[bullet_y][bullet_x] == FLOORCHARACTER)
            noCollision = false;
    }
    return noCollision;
}

//********** Nella seguente sezione viene gestito l'input da tastiera dell'utente **********

//switch-case per gestire le mosse del personaggio in base al tasto premuto dall'utente
void Hero::getmv(int choice){
            //napms(50);

            switch(choice){
                case KEY_UP:
            if (!(this->isJumping) && !(this->isFalling)){
                this->isJumping = true;
                this->jumpCounter = this->jumpForce;
                jump();
            }
            break;
        case KEY_LEFT:
            if(this->hit_direction != 2)
                if(check_map_collision(0))
                    mvleft();
            if(check_map_collision(3))
                this->isFalling = true;
            //napms(70); //tentativo di non velocizzare tutti i nemici quando si tiene premuta una freccia
            break;
        case KEY_RIGHT:
            if(this->hit_direction != 1)
                if(check_map_collision(1))
                    mvright();
            if(check_map_collision(3))
                this->isFalling = true;
            //napms(70); //tentativo di non velocizzare tutti i nemici quando si tiene premuta una freccia
            break;
        case ' ': //quando si preme la barra spaziatrice
            this->isAttacking = true;
            if(this->is_left){
                this->h = bullet_insert(this->h, this->xLoc, this->yLoc, true);
            }
            else{
                this->h = bullet_insert(this->h, this->xLoc+this->bound_right-1, this->yLoc, false);
            }
            break;
        default:
            break;
    }

    if(this->isJumping){
        if(choice != KEY_DOWN){
            jump();
        }
        else{
            this->isAttackingDown = true;
            this->isJumping = false;
            this->isFalling = true;
            fall();
        }
    }
    else if(this->isFalling){
        fall();
    }

    if(this->isAttacking){
        this->h = attack(h);
    }

}

//********** Nella seguente sezione si gestiscono l'interazione tra oggetti e eroe **********


void Hero::setStatChange(OggettoMarket o){
    double boost = 1.0 + o.getBoostStat(); //aumento percentuale completo
    //casting a int poichè le statistiche sono valori interi
    if(strcmp(o.getStatAffected(), "health")==0)
        this->setHealth((int)(this->getHealth() *boost)); //Modifica il valore di MAXHP quindi dovrebbe essere setMaxHP...
    else if(strcmp(o.getStatAffected(), "strenght")==0)
        this->setStrenght((int)(this->getStrenght() *boost));
    else if(strcmp(o.getStatAffected(), "defense")==0)
        this->setDefense((int)(this->getDefense() * boost));
    else if(strcmp(o.getStatAffected(), "luck")==0)
        this->setLuck((int)(this->getLuck() * boost));
}     
        
const char * Hero::purchase(OggettoMarket o){
    if(this->getMoney()>=o.getPrice()){
        this->setMoney(this->getMoney()-(o.getPrice()));
        this->setStatChange(o);
        (this->diff_level)++;
        return "ACQUISTO    AVVENUTO";
    }
    else{
        return "MONETE INSUFFICIENTI";
    }
}  

void Hero::setStatTemporary(OggettoMappa o){
    if(strcmp(o.getStatAffected(), "invincibility")==0)
        this->setInvincibility(true);
    else if(strcmp(o.getStatAffected(), "doubleMoney")==0)
        this->setDoubleMoney(true);
    else if(strcmp(o.getStatAffected(), "doubleScore")==0)
        this->setDoubleScore(true);
}

void Hero::setStatPermanent(OggettoMappa o){
    double boost = 1.0 + o.getBoostStat(); //aumento percentuale completo
    //casting a int poichè le statistiche sono valori interi
    if(strcmp(o.getStatAffected(), "health")==0) //Aumenta gli hp di boostStat rispetto ai maxHP
        this->setHealth((int)(this->getHealth() + this->getMaxHp()*boost));
   else if(strcmp(o.getStatAffected(), "strenght")==0)
        this->setStrenght((int)(this->getStrenght() *boost));
    else if(strcmp(o.getStatAffected(), "defense")==0)
        this->setDefense((int)(this->getDefense() * boost));
    else if(strcmp(o.getStatAffected(), "luck")==0)
        this->setLuck((int)(this->getLuck() * boost));
    else if(strcmp(o.getStatAffected(), "jumpForce")==0)
        this->setJumpForce((int)(this->getJumpForce() * boost));  
}

void Hero::setStatChange(OggettoMappa o){
    if(o.isTemporary())
        this->setStatTemporary(o);
    //La rimozione dell'effetto viene eseguita quando il personaggio passa al livello successivo
    else if(o.isSpecial()){ //CASO SCONTI
        //Parte di salvataggio su file 
        /* ifstream inputFile;  Dichiarazione di tipo 
	    char path[100] = "stat.txt"; //file dove vengono salvate le statistiche
        inputFile.open(path);
        string word;
	    if(!inputFile.fail()){
            while (inputFile >> word){
                if(strcmp(word, "Sconti:")==0){ //cerca stringa Sconti
                    inputFile<<"Y"; //Modifica a Y quello dopo
                    break;
                }
            }
        }
    }*/
    }
    else
        this->setStatPermanent(o);
}

//NOTA: dove la richiamiamo questa funzione??? Come capiamo qual è l'oggetto da passare??? Magari ogni mappa dovrebbe avere un attributo oggetto?
void Hero::hero_object_collision(OggettoMappa o){
    if(o.getYOgg() == (this->yLoc) || o.getYOgg() == (this->yLoc)+1){
        if(o.getXOgg() >= (this->xLoc) - 2 && o.getXOgg() <= (this->xLoc) + (this->bound_right) - 1){
            //CHIARA rimuovere l'oggetto (IDEA: attributo "used" in OggettoMappa: se è false (caso A), usare l'oggetto sull'eroe; 
            //se è true (caso B), non fare più la print dell'oggetto e non applicare l'effetto all'eroe)
            
            this->mapManager->GetCurrentMapList()->GetTail()->SetItemPicked(true);
            
            //Nota: le successive righe vanno eseguite SOLO nel caso A descritto prima.
            if(!(o.isTemporary())){
                (this->diff_level)++;
            }
        }
    }
}