#include "Enemy.h"

//funzione che fa muovere i nemici a destra e a sinistra
void Enemy::mv_left_right(){
    if (isFalling){
        fall();
    }

    if(is_left){
        if (check_map_collision(0))
            mvleft();
        else
            is_left = false;

        if(enemy_type != 3 && check_map_collision(3))
            isFalling = true;
    }
    else{
        if (check_map_collision(1))
            mvright();
        else
            is_left = true;

        if (enemy_type != 3 && check_map_collision(3))
            isFalling = true;
    }
}

//Funzione che controlla se un nemico è venuto a contatto con il personaggino.
void Enemy::check_enemy_player_collision(Hero *p){
    //se il nemico colpisce l'eroe da dx, quest'ultimo viene "spinto" verso sx
    if((p->xLoc >= xLoc - p->bound_right+1 && p->xLoc < xLoc) && (p->yLoc >= yLoc && p->yLoc <= yLoc + rows)&&!(p->getInvincibility())){
        p->is_hit = true;
        p->hit_direction = 1;
        if (p->check_map_collision(0))
            p->mvleft();
        if (p->check_map_collision(3))
            p->isFalling = true;
    }
    //se il nemico colpisce l'eroe da sx, quest'ultimo viene "spinto" verso dx
    else if((p->xLoc == xLoc + bound_right - 2) && (p->yLoc >= yLoc && p->yLoc <= yLoc + rows)&&!(p->getInvincibility())){
        p->is_hit = true;
        p->hit_direction = 2;
        if (p->check_map_collision(1))
            p->mvright();
        if (p->check_map_collision(3))
            p->isFalling = true;
    }
    //se il nemico colpisce l'eroe dal basso, quest'ultimo viene "fatto rimbalzare" verso l'alto; se l'eroe sta eseguendo un attacco dall'alto, allora è il nemico a subire danno
    else if((p->xLoc >= xLoc - p->bound_right+2 && p->xLoc <= xLoc + bound_right - 3) && (p->yLoc + p->rows == yLoc)&&!(p->getInvincibility())){
        if(!(p->isAttackingDown)){
            p->is_hit = true;
            p->hit_direction = 3;
            p->isJumping = true;
            p->isFalling = false;
            p->jumpCounter = p->jumpForce;
            p->jump();
        }
        else{
            hit_direction = 4;
            setHealth(getHealth() - p->getStrenght() + getDefense());
            if(getHealth() <= 0){
                //l'eroe guadagna soldi e punteggio
                if(p->getDoubleMoney())
                    p->setMoney((p->getMoney() + money_released)*2);
                else if(p->getDoubleScore())
                    p->score += score_released*2;
                else{ //caso in cui non sia stato preso nessun oggeto
                    p->setMoney(p->getMoney() + money_released);
                    p->score += score_released;
                }
            }
            else{
                //l'eroe guadagna un pochino di punteggio
                p->score += score_released/5;
            }
            p->isAttackingDown = false;
                    
            p->isJumping = true;
            p->isFalling = false;
            p->jumpCounter = p->jumpForce;
            p->jump();
        }
    }
    //se il nemico colpisce l'eroe dall'alto, quest'ultimo viene "fatto rimbalzare" verso il basso
    else if((p->xLoc >= xLoc - p->bound_right+2 && p->xLoc <= xLoc + bound_right - 3) && (p->yLoc == yLoc + rows)&&!(p->getInvincibility())){
        p->is_hit = true;
        p->hit_direction = 4;
        p->isJumping = false;
        p->isFalling = true;
        p->fall();
    }
            
    //Se l'eroe è entrato a contatto con un nemico, perde tanti punti vita (health) quanti sono i punti di forza (strenght) del nemico
    if(enemy_type!=2 && p->is_hit && getHealth()>0){ //per una iterazione, il nemico morto rimane visibile sottoforma di fantasma; in quel contesto non è però in grado di causare danno all'eroe. Per questo devo controllare getHealth().
        p->setHealth(p->getHealth() - getStrenght() + p->getDefense());
        p->is_hit = false;
    }
    else if(enemy_type==2 && p->is_hit && getHealth()>0){ //nel caso in cui l'eroe venga a contatto con un nemico di tipo ladro, perde soldi invece che punti vita
        p->setMoney(p->getMoney() - getStrenght());
        if(p->getMoney()<0)
            p->setMoney(0);
        p->is_hit = false;
    }
}

//Funzione che controlla se un nemico è venuto a contatto con un proiettile.
Hero::p_bullet Enemy::check_enemy_bullet_collision(Hero *p, Hero::p_bullet h){
            
    is_hit = false;

    if(h != NULL){
        int y = yLoc;
        int x_sx = xLoc-2, x_dx = xLoc+bound_right-1;

        //controllo il primo proiettile della lista di proiettili
        while(y < yLoc+rows && !is_hit){
            if((h->bullet_x >= x_sx && h->bullet_x <= x_dx) && h->bullet_y == y){
                is_hit = true;
                hit_direction = 1;
                setHealth(getHealth() - p->getStrenght() + getDefense());

                //rimuovo il proiettile
                Hero::p_bullet h2 = h;
                h = h->next;
                delete(h2);

                if(getHealth() <= 0){
                    //l'eroe guadagna soldi e punteggio
                    if(p->getDoubleMoney()){
                        p->setMoney(p->getMoney() + money_released*2);
                    }
                    else
                        p->setMoney(p->getMoney() + money_released);
                    if(p->getDoubleScore())
                        p->score += score_released*2;
                    else
                        p->score += score_released;
                }
                else{
                    //l'eroe guadagna un pochino di punteggio
                    p->score += score_released/5;
                }
            }
            y++;
        }
        //controllo dal secondo proiettile in poi
        Hero::p_bullet tmp = h;
        while(tmp!=NULL && (tmp->next)!=NULL){
            is_hit = false;
            y = yLoc;
            while(y < yLoc+rows && !is_hit){
                if(((tmp->next)->bullet_x >= x_sx && (tmp->next)->bullet_x <= x_dx) && (tmp->next)->bullet_y == y){    //se il nemico viene colpito da dx
                    is_hit = true;
                    hit_direction = 1;

                    //rimuovo il proiettile
                    Hero::p_bullet tmp2 = tmp->next;
                    tmp->next = (tmp->next)->next;
                    delete tmp2;
                }
                y++;
            }

            if(is_hit){
                setHealth(getHealth() - p->getStrenght() + getDefense());
                        
                if(getHealth() <= 0){
                    //l'eroe guadagna soldi e punteggio
                    if(p->getDoubleMoney()){
                        p->setMoney(p->getMoney() + money_released*2);
                    }
                    else
                        p->setMoney(p->getMoney() + money_released);
                    if(p->getDoubleScore())
                        p->score += score_released*2;
                    else
                        p->score += score_released;
                }
                else{
                    //l'eroe guadagna un pochino di punteggio
                    p->score += score_released/5;
                }
            }
            else{
                tmp = tmp->next;
            }
        }
    }
    return h;
}