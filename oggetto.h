#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <ncurses.h>
#include <cstring>
#include <chrono>

#define LEN 30
using namespace std;

class Oggetto{
    protected:
        char name[LEN];
        char skin; //carattere che rappresenta ogni ogggetto
        double boostStat; //valore in percentuale dell'effetto dell'oggetto
        char statAffected[LEN]; //nome della statistica che l'oggetto modifica

    public:
       virtual void setStatChange (/*Passo un oggetto Personaggio*/) = 0; //forse sarebbe meglio averle nella classe personaggio

};

class OggettoMarket : Oggetto{
    protected:
        double price;

    public:
        OggettoMarket(double price = 0.0, double boostStat = 0.0, char skin = ' ', char name[] = " ", char statAffected[] = " "){ //costruttore
            this -> price = price;
            this -> boostStat = boostStat;
            this -> sklin = skin;
            strcpy(this -> name, name);
            strcpy(this -> statAffected, statAffected);
        }

        void setStatChange (){
            //deve andare a modificare in percentuale boostStat l'attributo statAffected del personaggino
        }

        void purchase(){
            //check di quanti soldi ha il personaggio
            //se ne ha meno di price allora ritorna messaggio di errore

            else{
                //tolgo il valore di price al budget del personaggino
                setStatChange(/*Passo oggetto personaggio*/);
            }
        }
};

class OggettoMappa : Oggetto{
    protected:
        double probability; //probabilità in percentuale dello spawn dell'oggetto
        bool temporary; //vero quando l'effetto è temporaneo (dura solo per la prossima stanza)
        double special; //vero quando oggetto ha effetto nella run successiva

    public:
        OggettoMappa(double probability = 0.0, double timeDuration = 0.0, double price = 0.0, double boostStat = 0.0, char skin = ' ', char name[] = " ", char statAffected[] = " "){
            this -> probability = probability;
            this -> timeDuration = timeDuration;
            this -> price = price;
            this -> boostStat = boostStat;
            this -> sklin = skin;
            strcpy(this -> name, name);
            strcpy(this -> statAffected, statAffected);            
        }

        void removeStatChange(){
            //modifica in negativo 
        }

        void setStatChange(){
            if(temporary){ 
                //deve andare a modificare in percentuale boostStat l'attributo statAffected del personaggino
                //controllo quando esce dalla prossima stanza e poi
                removeStatChange();
            }
            else if(special){
                ifstream inputFile; /* Dichiarazione di tipo */
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
            }
            else{
                //deve andare a modificare in percentuale boostStat l'attributo statAffected del personaggino
            }
        }
}