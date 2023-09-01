#include "SetEnemiesList.h"
#include "Menu.h"
#include "FinestraP.h"
#include <string>

//la seguente funzione viene richiamata ad ogni "passo" del gioco
p_nodo game_loop(WINDOW* win, MapManager* mapManager, Hero* player, p_nodo h);
void player_skin_select(int key, Hero* player);
p_nodo map_change(WINDOW* win, MapManager* mapManager, Hero* player, p_nodo h);