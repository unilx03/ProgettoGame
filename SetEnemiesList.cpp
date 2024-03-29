#include "SetEnemiesList.h"

p_nodo head_insert(p_nodo h, WINDOW * playwin, int y, int x, MapManager* map, int enemy_type, bool left){
    p_nodo tmp = new nodo;

    //ogni tipologia di nemico viene identificata da un codice (un numero).
    switch(enemy_type){
        case 1:
            //nemico saltellante
            tmp->e = new JumpingEnemy(playwin, y, x, 1, 10, map, left);
            break;
        case 2:
            //nemico ladro
            tmp->e = new ThiefEnemy(playwin, y, x, 2, 8, map, left);
            break;
        case 3:
            //nemico volante di tipo Y
            tmp->e = new FlyingEnemyY(playwin, y, x, 3, 14, map, left);
            break;
        case 4:
            //nemico volante di tipo X
            tmp->e = new FlyingEnemyX(playwin, y, x, 4, 6, map, left);
            break;
        default:
            //nemico base
            tmp->e = new Enemy(playwin, y, x, 0, 10, map, left);
            break;
    }
    tmp->is_dead = false;
    tmp->next = h;
    return tmp;
}

//Funzione che stampa nella mappa tutti i nemici istanziati.
void display_list(p_nodo h){
    if(h != NULL){  //controllo di avere ancora elementi da stampare nella lista
        while(h != NULL){
            //switch-case che effettua il downcasting nella sottoclasse di Enemy corretta in base alla tipologia di nemico
            switch((h->e)->enemy_type){  
                case 1:
                    if((h->e)->getHealth()>0){
                        if((h->e)->hit_direction==0)
                            ((JumpingEnemy *)(h-> e))->display(((JumpingEnemy *)(h-> e))->enemy_shape_left, ((JumpingEnemy *)(h-> e))->enemy_shape_right);
                        else
                            ((JumpingEnemy *)(h-> e))->display(((JumpingEnemy *)(h-> e))->enemy_shape_left_hit, ((JumpingEnemy *)(h-> e))->enemy_shape_right_hit);
                    }
                    else{
                        h->is_dead = true;
                        ((JumpingEnemy *)(h-> e))->display(((JumpingEnemy *)(h-> e))->enemy_shape_dead, ((JumpingEnemy *)(h-> e))->enemy_shape_dead);
                    }
                    break;
                case 2:
                    if((h->e)->getHealth()>0){
                        if((h->e)->hit_direction==0)
                            ((ThiefEnemy *)(h-> e))->display(((ThiefEnemy *)(h-> e))->enemy_shape_left, ((ThiefEnemy *)(h-> e))->enemy_shape_right);
                        else
                            ((ThiefEnemy *)(h-> e))->display(((ThiefEnemy *)(h-> e))->enemy_shape_left_hit, ((ThiefEnemy *)(h-> e))->enemy_shape_right_hit);                           
                    }
                    else{
                        h->is_dead = true;
                        ((ThiefEnemy *)(h-> e))->display(((ThiefEnemy *)(h-> e))->enemy_shape_dead, ((ThiefEnemy *)(h-> e))->enemy_shape_dead);                           
                    }
                    break;
                case 3:
                    if((h->e)->getHealth()>0){
                        if((h->e)->hit_direction==0)
                            ((FlyingEnemyY *)(h-> e))->display(((FlyingEnemyY *)(h-> e))->enemy_shape, ((FlyingEnemyY *)(h-> e))->enemy_shape);
                        else
                            ((FlyingEnemyY *)(h-> e))->display(((FlyingEnemyY *)(h-> e))->enemy_shape_hit, ((FlyingEnemyY *)(h-> e))->enemy_shape_hit);
                    }
                    else{
                        h->is_dead = true;
                        ((FlyingEnemyY *)(h-> e))->display(((FlyingEnemyY *)(h-> e))->enemy_shape_dead, ((FlyingEnemyY *)(h-> e))->enemy_shape_dead);
                    }
                    break;
                case 4:
                    if((h->e)->getHealth()>0){
                        if((h->e)->hit_direction==0)
                            ((FlyingEnemyX *)(h-> e))->display(((FlyingEnemyX *)(h-> e))->enemy_shape, ((FlyingEnemyX *)(h-> e))->enemy_shape);
                        else
                            ((FlyingEnemyX *)(h-> e))->display(((FlyingEnemyX *)(h-> e))->enemy_shape_hit, ((FlyingEnemyX *)(h-> e))->enemy_shape_hit);
                    }
                    else{
                        h->is_dead = true;
                        ((FlyingEnemyX *)(h-> e))->display(((FlyingEnemyX *)(h-> e))->enemy_shape_dead, ((FlyingEnemyX *)(h-> e))->enemy_shape_dead);
                    }
                    break;
                default:
                    if((h->e)->getHealth()>0){
                        if((h->e)->hit_direction==0)
                            (h-> e)->display((h-> e)->enemy_shape_left, (h-> e)->enemy_shape_right);
                        else
                            (h-> e)->display((h-> e)->enemy_shape_left_hit, (h-> e)->enemy_shape_right_hit);
                    }
                    else{
                        h->is_dead = true;
                        (h-> e)->display((h-> e)->enemy_shape_dead, (h-> e)->enemy_shape_dead);
                    }
                    break;
            }
            (h->e)->hit_direction = 0;
            h = h->next; //passo al prossimo elemento della lista
        }  
    }
}

//Funzione che fa muovere tutti i nemici nella lista di un "passo".
p_nodo action_list(WINDOW * playwin, p_nodo h, Hero* player){
    if(h != NULL){  //controllo di avere ancora elementi nella lista

        //check del primo elemento
        if(h->is_dead){
            //rimuovo il nodo dalla lista
            p_nodo h2 = h;
            h = h->next;
            delete(h2);
        }

        //check dal secondo elemento in poi
        p_nodo tmp = h;
        while(tmp != NULL && (tmp->next) != NULL){
            if((tmp->next)->is_dead){
                //rimuovo il nodo dalla lista
                p_nodo tmp2 = tmp->next;
                tmp->next = (tmp->next)->next;
                delete tmp2;
            }
            else{
                tmp = tmp->next; //passo al prossimo elemento della lista
            }
        }

        //spostamento di un passo dei nemici
        tmp = h;
        while(tmp != NULL){
            (tmp->e)->check_enemy_player_collision(player); 
            player->h = (tmp->e)->check_enemy_bullet_collision(player, player->h);

            //switch-case che effettua il downcasting nella sottoclasse di Enemy corretta in base alla tipologia di nemico
            switch((tmp->e)->enemy_type){  
                case 1:
                    //il nemico saltellante si muove saltando a dx e a sx
                    ((JumpingEnemy *)(tmp -> e))->jump_and_fall();
                    break;
                case 2:
                    //il nemico ladro è simile a quello di tipo base, ma il giocatore perde soldi invece che punteggio a contatto con esso.
                    ((ThiefEnemy *)(tmp-> e))->mv_left_right();
                    break;
                case 3:
                    //il nemico volante di tipo Y fluttua in aria, muovendosi a dx e a sx (quindi mantenendo invariata l'ordinata Y).
                    ((FlyingEnemyY *)(tmp-> e))->mv_left_right();
                    break;
                case 4:
                    //il nemico volante di tipo X fluttua in aria, muovendosi su e giù (quindi mantenendo invariata l'ascissa X).
                    ((FlyingEnemyX *)(tmp-> e))->mv_up_down();
                    break;
                default:
                    //il nemico base si muove a destra e a sinistra.
                    (tmp->e)->mv_left_right();
                    break;
            }
            //}
            tmp = tmp->next; //passo al prossimo elemento della lista
        }  
    }
    return h;
}

void set_enemies_stats(p_nodo h, int diff_level){
    while(h != NULL){
        if((h->e)->enemy_type != 2)
            (h->e)->setStrenght((h->e)->DEF_ST + 2*diff_level);
        else
            (h->e)->setStrenght((h->e)->DEF_ST + diff_level);
        (h->e)->setDefense((h->e)->DEF_DF + diff_level);
        (h->e)->setHealth((h->e)->DEF_HP + 5*diff_level);
        ((h->e)->money_released) = (h->e)->DEF_MONEY + 5*diff_level;
        ((h->e)->score_released) = (h->e)->DEF_SCORE + 5*diff_level;

        h = h->next;
    }
}

//Funzione che prende in input il numero di nemici da generare e restituisce una lista di nemici posizionati sulla mappa
p_nodo generate_enemies(WINDOW * playwin, MapManager* map, int diff_level){
    p_nodo list = NULL;
    
    int num_enemies = NUM_ENEMIES_DEFAULT + diff_level/NUM_ENEMIES_GROWTH; //ogni volta che diff_level aumenta di NUM_ENEMIES_GROWTH viene aggiunto un nemico
    if (num_enemies > ENEMYSPAWN)
        num_enemies = ENEMYSPAWN;
    bool* isPositionTaken = new bool[ENEMYSPAWN];
    for (int i = 0; i < ENEMYSPAWN; i++)
        isPositionTaken[i] = false;

    int v[] = {0, 0, 0, 0, 0, 0, 1, 1, 2, 2, 2, 2, 3, 3, 4, 4}; //array da cui estrarre randomicamente il tipo di nemico da inserire in lista (notare che, ad esempio, il nemico di tipo 0 ha probabilità maggiore)
    random_shuffle(&v[0], &v[15]); //"scompiglia" gli elementi dell'array in modo casuale
    
    for(int i = 0; i<num_enemies; i++){ //seleziono randomicamente un elemento dell'array e inserisco nella lista il nemico corrispondente
        int index = 0;
        int spawn = 0;

        int x = 0, y = 0;

        index = rand()%16;

        if (v[index] != 4) //non nemico volante verticale
        {
            spawn = rand() % map->GetCurrentMapList()->GetTail()->GetNumSpawnEnemies();
                
            while (isPositionTaken[spawn])
            {
                spawn++;
                if (spawn >= map->GetCurrentMapList()->GetTail()->GetNumSpawnEnemies())
                    spawn = 0;

                if (!isPositionTaken[spawn])
                    isPositionTaken[spawn] = true;
            }

            x = map->GetCurrentMapList()->GetTail()->GetSpawnEnemies()[spawn].x;
            y = map->GetCurrentMapList()->GetTail()->GetSpawnEnemies()[spawn].y;
        }
        else
        {
            spawn = rand() % map->GetCurrentMapList()->GetTail()->GetNumSpawnFlyingEnemies();
                
            while (isPositionTaken[spawn + map->GetCurrentMapList()->GetTail()->GetNumSpawnEnemies()])
            {
                spawn++;
                if (spawn >= map->GetCurrentMapList()->GetTail()->GetNumSpawnFlyingEnemies())
                    spawn = 0;

                if (!isPositionTaken[spawn + map->GetCurrentMapList()->GetTail()->GetNumSpawnEnemies()])
                    isPositionTaken[spawn + map->GetCurrentMapList()->GetTail()->GetNumSpawnEnemies()] = true;
            }

            x = map->GetCurrentMapList()->GetTail()->GetSpawnFlyingEnemies()[spawn].x;
            y = map->GetCurrentMapList()->GetTail()->GetSpawnFlyingEnemies()[spawn].y;
        }

        int left_or_right = rand()%2; //decido randomicamente se il nemico si muove a dx o a sx (per i tipi 0, 1, 2, 3)
        bool left = false;
        if(left_or_right == 0)
            left = true;
        list = head_insert(list, playwin, y, x, map, v[index], left);
        (list->e)->yLoc -= (list->e)->rows;
    }
    set_enemies_stats(list, diff_level);
    return list;
}