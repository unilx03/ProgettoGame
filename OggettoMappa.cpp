#include "OggettoMappa.h"

void OggettoMappa::setStatTemporary(Hero* h){
    if(strcmp(statAffected, "invincibility")==0)
        h->setInvincibility(true);
    else if(strcmp(statAffected, "doubleMoney")==0)
        h->setDoubleMoney(true);
    else if(strcmp(statAffected, "doubleScore")==0)
        h->setDoubleScore(true);
}

void OggettoMappa::setStatPermanent(Hero* h){
    double boost = 1.0 + boostStat; //aumento percentuale completo
    //casting a int poichè le statistiche sono valori interi
    if(strcmp(statAffected, "health")==0) //Aumenta gli hp di boostStat rispetto ai maxHP
        h->setHealth((int)(h->getHealth() /*+ h.getMaxHp()*/ *boost));
    else if(strcmp(statAffected, "strenght")==0)
        h->setStrenght((int)(h->getStrenght() *boost));
    else if(strcmp(statAffected, "defense")==0)
        h->setDefense((int)(h->getDefense() * boost));
    else if(strcmp(statAffected, "luck")==0)
        h->setLuck((int)(h->getLuck() * boost));
    else if(strcmp(statAffected, "jumpForce")==0)
        h->setJumpForce((int)(h->getJumpForce() * boost));  
}

void OggettoMappa::setStatChange(Hero* h){
    if(temporary)
        setStatTemporary(h);
    //La rimozione dell'effetto viene eseguita quando il personaggio passa al livello successivo
    else if(special){
        //Parta di salvataggio su file 
          /* ifstream inputFile; /* Dichiarazione di tipo 
	            char path[100] = "stat.txt"; //file dove vengono salvate le statistiche
                inputFile.open(path);
                string word;
	            if(!inputFile.fail()){
                     while (inputFile >> word) {
                        if(strcmp(word, "Sconti:")==0){ //cerca stringa Sconti
                            inputFile<<"Y"; //Modifica a Y quello dopo
                            break;
                        }
                    }
                }
            }*/
    }
    else
        setStatPermanent(h);
}

const char * OggettoMappa::getSkin(){
    return skin;
}