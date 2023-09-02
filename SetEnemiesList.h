/*----------------------------------------------------------------------------------
I nemici vengono gestiti per mezzo di una lista dinamica.
----------------------------------------------------------------------------------*/

#include <ncurses/ncurses.h>
#include "FlyingEnemyX.h"
#include <algorithm>    // std::random_shuffle
#include <ctime>        // std::time
#include <cstdlib>      // std::rand, std::srand

const int NUM_ENEMIES_DEFAULT = 3; //numero di nemici presenti di default sulla mappa
const int NUM_ENEMIES_GROWTH = 5; //numero di livelli di difficoltà necessari per aumentare il numero di nemici di 1

struct nodo{    
    Enemy *e;
    bool is_dead;
    nodo *next;
};
typedef nodo* p_nodo;

p_nodo head_insert(p_nodo h, WINDOW * playwin, int y, int x, MapManager* map, int enemy_type);
void display_list(p_nodo h);
p_nodo action_list(WINDOW * playwin, p_nodo h, Hero* player);
void set_enemies_stats(p_nodo h, int diff_level);
p_nodo generate_enemies(WINDOW * playwin, MapManager* map, int diff_level);