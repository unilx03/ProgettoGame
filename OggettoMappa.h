#include "OggettoMarket.h"

class OggettoMappa : Oggetto{
    protected:
        double probability; //probabilità in percentuale dello spawn dell'oggetto
        bool temporary; //vero quando l'effetto è temporaneo (dura solo per la stanza corrente)
        bool special; //vero quando oggetto ha effetto nella run successiva
        
        //coordinate dell'oggetto nella mappa
        int xOgg;  
        int yOgg;

    public:

        OggettoMappa(const char * name, const char * skin, double boostStat, const char * statAffected, double probability, int xOgg = 0, int yOgg = 0, bool temporary = false, bool special = false){
            
            this -> name = new char[LEN];
            this -> name = name;
            this -> skin = new char;
            this -> skin = skin;
            this -> statAffected = new char[LEN];
            this -> statAffected = statAffected;
            this -> probability = probability;
            this -> boostStat = boostStat;
            this -> xOgg = xOgg;
            this -> yOgg = yOgg;
            this -> temporary = temporary;
            this -> special = special;

        }

        const char * getSkin(); 
        //ritorna la skin dell'oggetto  
        bool isTemporary();
        bool isSpecial(); 

        void setBoostStat(double boostStat);
        double getBoostStat();
        
        void setStatAffected(const char * statAffected);
        const char * getStatAffected();

        int getXOgg();
        void setXOgg(int xOgg);

        int getYOgg();
        void setYOgg(int yOgg);
  
};