#include "Oggetto.h"

class OggettoMarket : Oggetto{
    protected:
        double price;
        //SKIN solo per il market

    public:
        /*OggettoMarket(){

        }*/
        OggettoMarket(const char * name, const char * skin, double boostStat, const char * statAffected, double price){
            this -> name = new char[LEN];
            this -> name = name;
            this -> skin = new char;
            this -> skin = skin;
            this -> statAffected = new char[LEN];
            this -> statAffected = statAffected;
            this -> boostStat = boostStat;
            this -> price = price;
        }

        const char * purchase(Hero * h);
        /*
            Se il personaggio ha abbastanza soldi allora compra, vengono 
            modificate le stat e ritorna messaggio di avvenuto acquisto. Altrimenti messaggio di errore a schermo
        */

        const char * getSkin(); 
        //ritorna la skin dell'oggetto
        
        void setStatChange(Hero* h);
        /*
            Aumenta la statisticha statAffected della percentuale boostStat
        */
 
};