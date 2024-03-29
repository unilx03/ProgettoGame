#include <iostream>
#include <cstdlib>
#include <fstream>
#include <ncurses/ncurses.h> 

using namespace std;
#define LEN 15
#define N 5 //lunghezza vettore Market
#define M 8 //Lunghezza vettore dei drop (oggetti durante la run)

class Oggetto{
    protected:
        const char * name;
        const char * skin;
        double boostStat; //valore in percentuale dell'effetto dell'oggetto
        const char * statAffected; //nome della statistica che l'oggetto modifica

    public:
        const char * getSkin();
        void setBoostStat(double boostStat);
        double getBoostStat();
        void setStatAffected(const char * statAffected);
        const char * getStatAffected();
};    