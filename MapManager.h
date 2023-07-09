#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <ncurses.h>

#include "MapList.h"

using namespace std;

class MapManager
{
    protected:
        WINDOW* window;
        MapList* fullMapList;
        int numMaps;
        MapList* currentMapList;

    public:
        MapManager(WINDOW* win);
        void InitializeFullMapList();

        WINDOW* GetWindow();
        void SetWindow(WINDOW* w);

        MapList* GetFullMapList();
        void SetFullMapList(MapList* fml);

        int GetNumMaps();
        void SetNumMaps(int nm);

        MapList* GetCurrentMapList();
        void SetCurrentMapList(MapList* cml);

        void GenerateNewMap();

        void DrawCurrentMap();

        //Funzioni di salvataggio riguardo i livelli
        void LoadSavedMaps();
};

