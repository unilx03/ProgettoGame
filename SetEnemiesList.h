/*----------------------------------------------------------------------------------
I nemici vengono gestiti per mezzo di una lista dinamica.
----------------------------------------------------------------------------------*/

#include <ncurses/ncurses.h>
#include "BossEnemy.h"
#include <algorithm>    // std::random_shuffle
#include <ctime>        // std::time
#include <cstdlib>      // std::rand, std::srand

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

    int left_or_right = rand()%2; //decido randomicamente se il nemico si muove a dx o a sx (per i tipi 0, 1, 2, 3)
    bool left = false;
    if(left_or_right == 0)
        left = true;
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
        //NOTA PER ME: forse conviene gestire i boss nel file BossEnemy.cpp, e toglierli da questo switch case
        case 5:
            //nemico boss
            tmp->e = new BossEnemy(playwin, y, x, 5, 11, map, left);
            break;
        default:
            //nemico base
            tmp->e = new Enemy(playwin, y, x, 0, 10, map, left);
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
                case 1:
                    ((JumpingEnemy *)(h-> e))->jump_and_fall();
                    break;
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

//Funzione che prende in input il numero di nemici da generare e restituisce una lista di nemici posizionati sulla mappa
p_nodo generate_enemies(int num_enemies, WINDOW * playwin, MapManager* map){
    p_nodo list = NULL;
    
    int v[] = {0, 0, 0, 0, 0, 0, 1, 1, 2, 2, 2, 2, 3, 3, 4, 4}; //array da cui estrarre randomicamente il tipo di nemico da inserire in lista (notare che, ad esempio, il nemico di tipo 0 ha probabilità maggiore)
    random_shuffle(&v[0], &v[15]); //"scompiglia" gli elementi dell'array in modo casuale
    
    for(int i = 0; i<num_enemies; i++){ //seleziono randomicamente un elemento dell'array e inserisco nella lista il nemico corrispondente
        int index = rand()%16;

        //NOTA: solo un esempio, da implementare un posizionamento più serio
        int p;
        switch(v[index]){ 
            case 1:
                p = rand()%2;
                if(p == 0)
                    list = head_insert(list, playwin, 10, 140, map, 1);
                else
                    list = head_insert(list, playwin, 10, 120, map, 1);
                break;
            case 2:
                p = rand()%2;
                if(p == 0)
                    list = head_insert(list, playwin, 9, 100, map, 2);
                else
                    list = head_insert(list, playwin, 15, 70, map, 2);
                break;
            case 3:
                p = rand()%2;
                if(p == 0)
                    list = head_insert(list, playwin, 7, 30, map, 3);
                else
                    list = head_insert(list, playwin, 13, 80, map, 3);
                break;
            case 4:
                p = rand()%2;
                if(p == 0)
                    list = head_insert(list, playwin, 17, 150, map, 4);
                else
                    list = head_insert(list, playwin, 15, 4, map, 4);
                break;
            default:
                p = rand()%2;
                if(p == 0)
                    list = head_insert(list, playwin, 10, 150, map, 0);
                else
                    list = head_insert(list, playwin, 4, 80, map, 0);
                break;
        }
    }
    return list;
}