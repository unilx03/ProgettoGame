#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <ncurses/ncurses.h>

#include "Map.h"


using namespace std;

class MapList
{
    protected:
        Map* tail;

    public:
        MapList ();

        Map* GetTail();
        void SetTail(Map* t);

        void AddMap (Map* node);
        Map* LoadMapFromID (Map* tail, int id);
        int CountMaps (Map* tail);

        void PrintMaps(Map* tail);

        void NextMap ();
        void PreviousMap ();
};