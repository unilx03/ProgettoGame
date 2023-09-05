#include <ncurses.h>
#include <string>
#include <fstream>
using namespace std;


void creaFileStat(){
string nome="Bunny";
string difesa="0";
string vita="25";
string attacco="1";
string soldi="0";
string puntif="0";
string score="0";
string livello="1";
string dif_lev="0";
ofstream fout;
fout.open("Personaggio.txt"); // apre il file in scrittura
fout << nome << endl; // scrive sul file
fout << vita << endl;
fout << soldi << endl;
fout << difesa << endl;
fout << attacco << endl;
fout << puntif << endl;
fout << livello << endl;
fout << score << endl;
fout << dif_lev << endl
fout.close();
}

void saveCharacterStats(string nome, int difesa, int vita, int attacco, int soldi, int puntif, int score, int livello, int def_lev) {
    ofstream fout;
    fout.open("Personaggio.txt"); // apre il file in scrittura
    fout << nome << endl; // scrive sul file
    fout << vita << endl;
    fout << soldi << endl;
    fout << difesa << endl;
    fout << attacco << endl;
    fout << puntif << endl;
    fout << livello << endl;
    fout << score << endl;
    fout << def_lev << endl;
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
    WINDOW *menuwinG= newwin(22,28, 2, 1+166);
    box(menuwinG, 0,0);


    //refresh();

    //wrefresh() copia la finestra indicata sullo schermo fisico del terminale,
    //tenendo presente quanto vi si trova gi� allo scopo di ottimizzare

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
        mvwprintw(menuwinG, 5,14,"$$$:");
        mvwprintw(menuwinG, 10,2,"DEF:");
        mvwprintw(menuwinG, 10,14,"ATT:");
        mvwprintw(menuwinG, 15,2,"FP :");
        mvwprintw(menuwinG, 15,14,"LEV:");
        mvwprintw(menuwinG, 20,2,"SCORE:");

        if(i==5)
            mvwprintw(menuwinG, (i-1)*5, n*14+9, "%s ",t.c_str());
        else
            mvwprintw(menuwinG, (i-1)*5, n*14+6,"%s ",t.c_str());

        n++;
        }
    }
    f.close();

    wrefresh(menuwinG);
}

void perdita(){

    WINDOW *menuwinG= newwin(22,162, 2, 5);


    refresh();
    mvwprintw(menuwinG,3,2,"|||||             ||||||      ||||||||||      ||||           ||||            ||||||||||||||            ||||||   ||||||||||||||||||   ||||||||||||||             ");
    mvwprintw(menuwinG,4,2,"|||||             ||||||    ||||||||||||||    ||||           ||||            ||||||||||||||            ||||||   ||||||||||||||||||   ||||||||||||||             ");
    mvwprintw(menuwinG,5,2," |||||           ||||||   ||||||      ||||||  ||||           ||||            ||||||      ||||||        ||||||   ||||||               ||||||      ||||||         ");
    mvwprintw(menuwinG,6,2,"  |||||         ||||||    ||||          ||||  ||||           ||||            ||||||      ||||||        ||||||   ||||||               ||||||      ||||||         ");
    mvwprintw(menuwinG,7,2,"   |||||       ||||||     ||||          ||||  ||||           ||||            ||||||          ||||||    ||||||   ||||||               ||||||          ||||||     ");
    mvwprintw(menuwinG,8,2,"    |||||     ||||||      ||||          ||||  ||||           ||||            ||||||          ||||||    ||||||   ||||||               ||||||          ||||||     ");
    mvwprintw(menuwinG,9,2,"      ||||   ||||         ||||          ||||  ||||           ||||            ||||||            ||||||  ||||||   ||||||               ||||||            ||||||   ");
    mvwprintw(menuwinG,10,2,"        ||||||            ||||          ||||  ||||           ||||            ||||||            ||||||  ||||||   ||||||||||||||||||   ||||||            ||||||   ");
    mvwprintw(menuwinG,11,2,"        ||||||            ||||          ||||  ||||           ||||            ||||||            ||||||  ||||||   ||||||||||||||||||   ||||||            ||||||   ");
    mvwprintw(menuwinG,12,2,"        ||||||            ||||          ||||  ||||           ||||            ||||||            ||||||  ||||||   ||||||               ||||||            ||||||   ");
    mvwprintw(menuwinG,13,2,"        ||||||            ||||          ||||  ||||           ||||            ||||||          ||||||    ||||||   ||||||               ||||||          ||||||     ");
    mvwprintw(menuwinG,14,2,"        ||||||            ||||          ||||  ||||           ||||            ||||||          ||||||    ||||||   ||||||               ||||||          ||||||     ");
    mvwprintw(menuwinG,15,2,"        ||||||            ||||          ||||  ||||           ||||            ||||||      ||||||        ||||||   ||||||               ||||||      ||||||         ");
    mvwprintw(menuwinG,16,2,"        ||||||            ||||||      ||||||  ||||||        |||||            ||||||      ||||||        ||||||   ||||||               ||||||      ||||||         ");
    mvwprintw(menuwinG,17,2,"        ||||||              ||||||||||||||      ||||||    |||||              ||||||||||||||            ||||||   ||||||||||||||||||   ||||||||||||||             ");
    mvwprintw(menuwinG,18,2,"        ||||||               |||||||||||          ||||||||||                 ||||||||||||||            ||||||   ||||||||||||||||||   ||||||||||||||             ");

    box(menuwinG, 0,0);

    wrefresh(menuwinG);
}

void inseriscinome() {

    // Crea una finestra per l'input
    WINDOW *namewin = newwin(22, 162, 2, 5);
    box(win, 0, 0);
    refresh();

    // Stampa un prompt
    mvwprintw(namewin, 1, 1, "Inserisci un nome: ");
    wrefresh(namewin);

    // Crea un buffer per l'input dell'utente
    char nome[32];
    echo(); // Abilita l'eco (visualizza ciò che viene digitato)
    mvwgetnstr(namewin, 2, 1, nome, sizeof(nome)); // Mostra ciò che l'utente digita
    noecho(); // Disabilita l'eco

    saveCharacterStats(nome,0, 25, 1, 0, 0, 0, 1, 0);
    wrefresh(namewin);
}
