#include <iostream>
#include <fstream>
#include <ncurses.h>

using namespace std;

struct punto{
    int x;
    int y;
};

struct livello{
    int mappa[120][20];
    punto spawnNemici[80];
    punto spawnOggetti[3];
};

void start();
livello letturaMappa();
void disegnaMappa(livello l);