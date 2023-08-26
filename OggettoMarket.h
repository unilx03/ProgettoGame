#include "Oggetto.h"

class OggettoMarket : Oggetto{
    protected:
        int price;
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


        const char * getSkin(); 
        //ritorna la skin dell'oggetto

        int getPrice();
        void setPrice(int price);

        void setBoostStat(double boostStat);
        double getBoostStat();

        void setStatAffected(const char * statAffected);
        const char * getStatAffected();
        
 
};