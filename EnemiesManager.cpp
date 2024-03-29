#include "EnemiesManager.h"

//Inserisce un lista di nemici in coda alla lista di liste
p_en_list tail_insert(p_en_list h, p_nodo enemies){
    if(h == NULL){
        p_en_list tmp = new enemiesList;
        tmp->list = enemies;
        tmp->next = NULL;
        tmp->prev = NULL;
        return tmp;
    }
    else{
        p_en_list tmp = h;
        while(tmp->next != NULL)
            tmp = tmp->next;
        tmp->next = new enemiesList;
        p_en_list tmp2 = tmp->next;
        tmp2->prev = tmp;
        tmp2->list = enemies;
        tmp2->next = NULL;
        return h;
    }
}

//Cerca la lista di nemici associata al livello dato in input (sapendo che al livello i-esimo corrisponde la lista i-esima)
p_en_list search_enemies(p_en_list h, int level){
    if(h != NULL){
        for(int i = 1; i < level; i++){
            h = h->next;
        }
    }
    return h;
}
