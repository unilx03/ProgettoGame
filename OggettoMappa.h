#include "Oggetto.h"

class OggettoMappa : Oggetto{
    protected:
        double probability; //probabilità in percentuale dello spawn dell'oggetto
        bool temporary; //vero quando l'effetto è temporaneo (dura solo per la stanza corrente)
        bool special; //vero quando oggetto ha effetto nella run successiva
        //gli oggetti sono già presenti all'inizio della stanza

    public:
        OggettoMappa(const char * name, const char * skin, double boostStat, const char * statAffected, double probability, bool temporary = false, bool special = false){
            
            this -> name = new char[LEN];
            this -> name = name;
            this -> skin = new char;
            this -> skin = skin;
            this -> statAffected = new char[LEN];
            this -> statAffected = statAffected;
            this -> probability = probability;
            this -> boostStat = boostStat;
            this -> temporary = temporary;
            this -> special = special;

        }

        void setStatTemporary(Hero h); 
        //Controlla se l'oggetto raccolto è un oggetto temporaneo e modifica stat

        void setStatPermanent(Hero h);
        //Modifica le statistiche permanenti in base all'effetto dell'oggetto

        const char * getSkin(); 
        //ritorna la skin dell'oggetto

        void setStatChange(Hero h); 
        //Modifica le statistiche in base all'oggetto raccolto     
  
};