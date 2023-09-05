#include "SetEnemiesList.h"

struct enemiesList{    
    p_nodo list;
    enemiesList *next;
    enemiesList *prev;
};
typedef enemiesList* p_en_list;

p_en_list tail_insert(p_en_list h, p_nodo enemies);

p_en_list search_enemies(p_en_list h, int level);
