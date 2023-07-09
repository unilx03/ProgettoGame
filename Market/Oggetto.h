#include <iostream>
#include <cstdlib>
#include <fstream>
#include <ncurses/ncurses.h> 
#include "Hero.h"

using namespace std;
#define LEN 15
#define N 5 //lunghezza vettore Market
#define M 9 //Lunghezza vettore dei drop (oggetti durante la run)

class Oggetto{
    protected:
        const char * name;
        const char * skin;
        double boostStat; //valore in percentuale dell'effetto dell'oggetto
        const char * statAffected; //nome della statistica che l'oggetto modifica

    public:
        virtual const char * getSkin() = 0; //ritorna la skin dell'oggetto
        virtual void setStatChange (Hero h) = 0; //metodo astratto
};    