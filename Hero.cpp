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
            break;
        case KEY_RIGHT:
            if(this->hit_direction != 1)
                if(check_map_collision(1))
                    mvright();
            if(check_map_collision(3))
                this->isFalling = true;
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

    if(strcmp(o.getStatAffected(), "Health")==0){
        int health = (int)(this->getMaxHp() *boost);
        this->setMaxHp(health); 
        this->setHealth(health);
        (this->diff_level)++;
    }
    else if(strcmp(o.getStatAffected(), "Strenght")==0){
        this->setStrenght((int)(this->getStrenght() *boost));
        (this->diff_level)++;
    }
    else if(strcmp(o.getStatAffected(), "Defense")==0){
        this->setDefense((int)(this->getDefense()+5)); 
        (this->diff_level)++;
    }
    else if(strcmp(o.getStatAffected(), "Luck")==0)
        this->setLuck((this->getLuck()+1)); 
    else
        this->setJumpForce(this->getJumpForce()+1); 
}

const char * Hero::purchase(OggettoMarket o){
    if(this->getMoney()>=o.getPrice()){
        this->setMoney(this->getMoney()-(o.getPrice()));
        this->setStatChange(o);
        return "ACQUISTO    AVVENUTO";
    }
    else{
        return "MONETE INSUFFICIENTI";
    }
}

void Hero::setStatTemporary(OggettoMappa o){
    if(strcmp(o.getStatAffected(), "Invincibility")==0)
        this->setInvincibility(true);
    else if(strcmp(o.getStatAffected(), "Double Money")==0)
        this->setDoubleMoney(true);
    else if(strcmp(o.getStatAffected(), "Double Score")==0)
        this->setDoubleScore(true);
}

void Hero::setStatPermanent(OggettoMappa o){
    double boost = 1.0 + o.getBoostStat(); //aumento percentuale completo

    if(strcmp(o.getStatAffected(), "Health")==0) 
        this->setHealth(getMaxHp());
   else if(strcmp(o.getStatAffected(), "Strenght")==0){
            this->setStrenght((int)(this->getStrenght() *boost));
            (this->diff_level)++;
   }
    else if(strcmp(o.getStatAffected(), "Defense")==0){
        this->setDefense(this->getDefense()+5);
        (this->diff_level)++;
    }
    else if(strcmp(o.getStatAffected(), "Jump Force")==0)
        this->setJumpForce(this->getJumpForce()+1);
}

void Hero::setStatChange(OggettoMappa o){
    if(o.isTemporary())
        this->setStatTemporary(o);
    //La rimozione dell'effetto viene eseguita quando il personaggio passa al livello successivo
    else if(o.isSpecial()){
                string nomep = selezionenome();
				int datiuser[10];
				vettoredati(datiuser);
                this -> setSale(1);
				saveCharacterStats(nomep, datiuser[2], datiuser[0], datiuser[3], datiuser[1], datiuser[4], datiuser[6], datiuser[5], datiuser[7], 1, datiuser[9]);
    }
    else
        this->setStatPermanent(o);
}

void Hero::hero_object_collision(OggettoMappa o){
    //Oggetto già raccolto
    if (this->mapManager->GetCurrentMapList()->GetTail()->GetItemPicked())
        return;
        
    //Oggetto non ancora raccolto
    if(o.getYOgg() == (this->yLoc) || o.getYOgg() == (this->yLoc)+1){
        if(o.getXOgg() >= (this->xLoc) - 2 && o.getXOgg() <= (this->xLoc) + (this->bound_right) - 1){
            this->setStatChange(o);
            this->has_found_obj = true;
            this->mapManager->GetCurrentMapList()->GetTail()->SetItemPicked(true);
        }
    }
}

//********** Funzioni che servono per modificare e prendere info dal file *************

//Scrivo lo stato corrente dell'eroe su file
void saveCharacterStats(string nome, int difesa, int vita, int attacco, int soldi, int puntif, int score, int livello, int dif_lev, int sconto, int maxhp) {
    ofstream fout;
    fout.open("Personaggio.txt"); // apre il file in scrittura
    fout << nome << endl; // scrive sul file
    fout << vita << endl;
    fout << soldi << endl;
    fout << difesa << endl;
    fout << attacco << endl;
    fout << puntif << endl;
    fout << livello << endl;
    fout << score << endl;
    fout << dif_lev << endl;
    fout << sconto << endl;
    fout << maxhp << endl;
    fout.close();
}

//Leggo il nome dell'eroe da file
string selezionenome(){
    //f.open("Personaggio.txt");
    ifstream file ("Personaggio.txt");
    string line;
    getline(file, line);
    file.close();
    return line;
}

//Leggo tutte le statistiche associate all'eroe da file
void vettoredati(int dati[]){
    //f.open("Personaggio.txt");
    ifstream file ("Personaggio.txt");
    string line;
    int i=0;
    getline(file, line);
    while( getline(file, line)){
    dati[i]=stoi(line);
    i++;
    }
    file.close();
}
