#include <ncurses.h>
#include <string>
#include<fstream>
using namespace std;


void creaFileStat(){
string nome="Bunny";
string punteggio="0";
string vita="50";
string attacco="15";
string soldi="5";
string puntif="5";
string score="5";
string livello="1";
 ofstream fout;
 fout.open("Personaggio.txt"); // apre il file in scrittura
 fout << nome << endl; // scrive sul file
 fout << punteggio << endl;
 fout << vita << endl;
 fout << attacco << endl;
 fout << soldi << endl;
 fout << puntif << endl;
 fout << score << endl;
 fout << livello << endl;
 fout.close();
}


void creaFinestra(){
    ifstream f;
    f.open("Personaggio.txt");
    //CONTROLLO CHE datis.txt ESISTA, SE NON ESISTE LO CREO CON UN SET BASE
    if(!f.is_open() || f.peek()==EOF){
        f.close();
        creaFileStat();
        f.open("Personaggio.txt");
    }




    //misure dello screen
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);

    //creo una finestra per l'input
    WINDOW *menuwinG= newwin(18,35, 0, 1);
    box(menuwinG, 0,0);


    refresh();

    //wrefresh() copia la finestra indicata sullo schermo fisico del terminale,
    //tenendo presente quanto vi si trova già allo scopo di ottimizzare

    //LAVORO SULLA FINESTRA DI SFONDO
    mvwprintw(menuwinG,1,2,"Player:");



     int i=0;
     int n=0;
     string v[50];
    while(!f.eof()){   //METTO TUTTE LE RIGHE DEL FILE DENTRO UN VETTORE DI STRINGHE       RICORDA: Riga-->0: Nome; Riga-->1: Punteggio;
        string t;
        getline(f,t);
        if(n==0 && i==0){
            mvwprintw(menuwinG, 1,12,"%s ",t.c_str());
            i++;
        }else{

        if(n%2==0){
            i++;
            n=0;
        }
        mvwprintw(menuwinG, 5,2,"HP :");
        mvwprintw(menuwinG, 5,14,"ATT:");
        mvwprintw(menuwinG, 10,2,"DEF:");
        mvwprintw(menuwinG, 10,14,"$$$:");
        mvwprintw(menuwinG, 15,2,"FP :");
        mvwprintw(menuwinG, 15,14,"LEV:");
        mvwprintw(menuwinG, 20,2,"SCORE:");

        if(i==5)
            mvwprintw(menuwinG, (i-1)*5+3,n*14+6,"%s ",t.c_str());
        else
            mvwprintw(menuwinG, (i-1)*5,n*14+6,"%s ",t.c_str());

        n++;
        }
    }
    f.close();

    wrefresh(menuwinG);
}
