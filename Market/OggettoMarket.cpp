#include "OggettoMarket.h"
const char * OggettoMarket::purchase(Hero h){
    if(h.getMoney()>=price){
        h.setMoney(h.getMoney()-price);
        setStatChange(h);
        return "Acquisto avvenuto";
    }
    else{
        return "Monete insufficienti";
    }
}

void OggettoMarket::setStatChange(Hero h){
    double boost = 1.0 + boostStat; //aumento percentuale completo
    //casting a int poichè le statistiche sono valori interi
    if(strcmp(statAffected, "health")==0)
        h.setHealth((int)(h.getHealth() *boost)); //Modifica il valore di MAXHP quindi dovrebbe essere setMaxHP...
    else if(strcmp(statAffected, "strenght")==0)
        h.setStrenght((int)(h.getStrenght() *boost));
    else if(strcmp(statAffected, "defense")==0)
        h.setDefense((int)(h.getDefense() * boost));
    else if(strcmp(statAffected, "luck")==0)
        h.setLuck((int)(h.getLuck() * boost));
    else if(strcmp(statAffected, "attackSpeed")==0)
        h.setAttackSpeed((int)(h.getAttackSpeed() * boost));
}