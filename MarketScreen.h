#include "SetEnemiesList.h"
#define ROW 30
#define COLUMN 160
#define HEIGHT 9
#define WIDTH 16
//Stampa l'intera schermata del market
void printScreen(WINDOW* win, WINDOW* item1, WINDOW* item2, WINDOW* item3, WINDOW* item4, WINDOW* item5, WINDOW* item6, OggettoMarket* m[]);


//Funzione per la stampa dell'evidenziazione
void printHighlight(WINDOW* item1, WINDOW* item2, WINDOW* item3, WINDOW* item4, WINDOW* item5, WINDOW* item6, int highlight);

//Spostamento evidenziazione
void changeHighlight(int choice, int & highlight, bool & cont);

//Controlla la scelta
bool checkChoice(int choice, int highlight, bool cont, WINDOW* win, WINDOW* item1, WINDOW* item2, WINDOW* item3, WINDOW* item4, WINDOW* item5, WINDOW* item6, OggettoMarket* m[], Hero * h);