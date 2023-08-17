/*----------------------------------------------------------------------------------
I nemici vengono gestiti per mezzo di una lista dinamica.
----------------------------------------------------------------------------------*/

#include <ncurses/ncurses.h>
#include "BossEnemy.h"

//NOTA PER ME: fare una lista di costanti con i numeri identificativi dei nemici.

//NOTA PER ME: spostare tutte queste funzioni in un file .cpp. Lasciare qui la dichiarazione del nodo.

//NOTA PER ME: un'alternativa è di mettere la struct in Character.h, e di effettuare il downcasting da lì a tutte le altre classi.
struct nodo{    
    Enemy *e;
    nodo *next;
};
typedef nodo* p_nodo;

//NOTA PER ME: gestendo il tutto in certo modo (considerata anche la funzione seguente), tutti i file nemico.cpp diventano inutili.
p_nodo head_insert(p_nodo h, WINDOW * playwin, int y, int x, MapManager* map, int enemy_type){
    p_nodo tmp = new nodo;
    //ogni tipologia di nemico viene identificata da un codice (un numero).
    switch(enemy_type){
        case 1:
            //nemico saltellante
            tmp->e = new JumpingEnemy(playwin, y, x, 1, 10, map);
            break;
        case 2:
            //nemico ladro
            tmp->e = new ThiefEnemy(playwin, y, x, 2, 8, map);
            break;
        case 3:
            //nemico volante di tipo Y
            tmp->e = new FlyingEnemyY(playwin, y, x, 3, 14, map);
            break;
        case 4:
            //nemico volante di tipo X
            tmp->e = new FlyingEnemyX(playwin, y, x, 4, 6, map, true);
            break;
        //NOTA PER ME: forse conviene gestire i boss nel file BossEnemy.cpp, e toglierli da questo switch case
        case 5:
            //nemico boss
            tmp->e = new BossEnemy(playwin, y, x, 5, 11, map);
            break;
        default:
            //nemico base
            tmp->e = new Enemy(playwin, y, x, 0, 10, map);
            break;
    }
    tmp->next = h;
    return tmp;
}

//NOTA PER ME: servirà una funzione di rimozione che rimuova dalla lista i nemici la cui vita scenda a 0.

//Funzione che stampa nella mappa tutti i nemici istanziati.
void display_list(p_nodo h){
    if(h != NULL){  //controllo di avere ancora elementi da stampare nella lista
        while(h != NULL){
            //switch-case che effettua il downcasting nella sottoclasse di Enemy corretta in base alla tipologia di nemico
            switch((h->e)->enemy_type){  
                case 1:
                    ((JumpingEnemy *)(h-> e))->display(((JumpingEnemy *)(h-> e))->enemy_shape_left, ((JumpingEnemy *)(h-> e))->enemy_shape_right);
                    break;
                case 2:
                    ((ThiefEnemy *)(h-> e))->display(((ThiefEnemy *)(h-> e))->enemy_shape_left, ((ThiefEnemy *)(h-> e))->enemy_shape_right);
                    break;
                case 3:
                    ((FlyingEnemyY *)(h-> e))->display(((FlyingEnemyY *)(h-> e))->enemy_shape, ((FlyingEnemyY *)(h-> e))->enemy_shape);
                    break;
                case 4:
                    ((FlyingEnemyX *)(h-> e))->display(((FlyingEnemyX *)(h-> e))->enemy_shape, ((FlyingEnemyX *)(h-> e))->enemy_shape);
                    break;
                //NOTA PER ME: forse conviene gestire i boss nel file BossEnemy.cpp, e toglierli da questo switch case
                case 5:
                    ((BossEnemy *)(h-> e))->display(((BossEnemy *)(h-> e))->enemy_shape, ((BossEnemy *)(h-> e))->enemy_shape);
                    break;
                default:
                     (h-> e)->display((h-> e)->enemy_shape_left, (h-> e)->enemy_shape_right);
                    break;
            }
            h = h->next; //passo al prossimo elemento della lista
        }  
    }
}

//Funzione che fa muovere tutti i nemici nella lista di un "passo".
void action_list(WINDOW * playwin, p_nodo h){
    if(h != NULL){  //controllo di avere ancora elementi da stampare nella lista
        while(h != NULL){
            //wtimeout(playwin, 70); //permette al nemico di muoversi indipendentemente dagli input dell'utente
            //switch-case che effettua il downcasting nella sottoclasse di Enemy corretta in base alla tipologia di nemico
            switch((h->e)->enemy_type){  
                /*case 1:
                    ((JumpingEnemy *)(h-> e))->jump(((JumpingEnemy *)(h-> e))->enemy_shape_left, ((JumpingEnemy *)(h-> e))->enemy_shape_right);
                    ((JumpingEnemy *)(h-> e))->fall(((JumpingEnemy *)(h-> e))->enemy_shape_left, ((JumpingEnemy *)(h-> e))->enemy_shape_right);
                    break;*/
                case 2:
                    //il nemico ladro è simile a quello di tipo base, ma il giocatore perde soldi invece che punteggio a contatto con esso.
                    ((ThiefEnemy *)(h-> e))->mv_left_right();
                    break;
                case 3:
                    //il nemico volante di tipo Y fluttua in aria, muovendosi a dx e a sx (quindi mantenendo invariata l'ordinata Y).
                    ((FlyingEnemyY *)(h-> e))->mv_left_right();
                    break;
                case 4:
                    //il nemico volante di tipo X fluttua in aria, muovendosi su e giù (quindi mantenendo invariata l'ascissa X).
                    ((FlyingEnemyX *)(h-> e))->mv_up_down();
                    break;
                //NOTA PER ME: forse conviene gestire i boss nel file BossEnemy.cpp, e toglierli da questo switch case
                /*case 5:
                    ((BossEnemy *)(h-> e))->display(((BossEnemy *)(h-> e))->enemy_shape, ((BossEnemy *)(h-> e))->enemy_shape);
                    break;*/
                default:
                    //il nemico base si muove a destra e a sinistra.
                    (h->e)->mv_left_right();
                    break;
            }
            h = h->next; //passo al prossimo elemento della lista
        }  
    }
}

//NOTA PER ME: se tutto va come deve andare, bisognerà richiamare display_list e action_list ad ogni "passo" delle funzioni salto e sparo proiettile dell'eroe

/*
NOTA PER ME: per far funzionare la funzione provaaa() definita sotto è stato disattivato un wclear
nella funzione display.
*/



/*void provaaa(WINDOW * playwin, int yHero, int xHero, p_nodo h){
        char name[7] = "Ettore";
        Hero * c = new Hero(playwin, yHero, xHero, 8, name);
        do{     
                wclear(playwin);

                display_list(h);
                action_list(playwin, h);

                c->display(c->player_shape_left, c->player_shape_right);
        }while(c->getmv()!='x');
}*/