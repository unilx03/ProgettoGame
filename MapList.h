#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <ncurses.h>

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

        void addMap (Map* node);
        Map* loadMapFromID (Map* tail, int id);
        int countMaps (Map* tail);

        void printMaps(Map* tail);

        void nextMap ();
        void previousMap ();
};