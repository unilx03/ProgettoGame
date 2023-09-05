
#include "Menu.h"
using namespace std;

void stampaConiglio(WINDOW *f, int n){
    if(n==0){
    mvwprintw(f, 3,n*45+4,"  (%c /)",92);
    mvwprintw(f, 4,n*45+4,"( ='.')");

    mvwprintw(f, 3,(n+1)*45+4,"       ");
    mvwprintw(f, 4,(n+1)*45+4,"       ");

    mvwprintw(f, 3,(n+2)*45+4,"       ");
    mvwprintw(f, 4,(n+2)*45+4,"       ");
    }
    else{
        if(n==1){
             mvwprintw(f, 3,(n-1)*45+4,"       ");
             mvwprintw(f, 4,(n-1)*45+4,"       ");

             mvwprintw(f, 3,n*45+4,"  (%c /)",92);
             mvwprintw(f, 4,n*45+4,"( ='.')");

             mvwprintw(f, 3,(n+1)*45+4,"       ");
             mvwprintw(f, 4,(n+1)*45+4,"       ");

        }
        else{
             mvwprintw(f, 3,(n-2)*45+4,"       ");
             mvwprintw(f, 4,(n-2)*45+4,"       ");

             mvwprintw(f, 3,(n-1)*45+4,"       ");
             mvwprintw(f, 4,(n-1)*45+4,"       ");

             mvwprintw(f, 3,n*45+4,"  (%c /)",92);
             mvwprintw(f, 4,n*45+4,"( ='.')");

        }
    }



}
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
string sconto="0";
string maxhp="600"; //devo inserire il valore giusto
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
fout << dif_lev << endl;
fout << sconto << endl;
fout << maxhp << endl;
fout.close();
}

void selezionoScore(string v[]){
    //f.open("Personaggio.txt");
    ifstream file ("Personaggio.txt");
    string line;
    getline(file, line);
    v[0]=line;
    for(int i=0; i<7;i++){
        getline(file, line);
    }
    v[1]=line;
    file.close();
}

/*int cercaRecord(string v[], int n){
    int j=1;
    int cont=1;
    while(j<n-2){
    if(stoi(v[j])<stoi(v[j+2])){   //in caso di parit� tengo il vecchio campione
    cont=j+2;
    }
    j+=2;
    }
    return cont-1;
}*/


int create_menu(){
    //NCURSES START
    /*initscr();
    noecho();
    cbreak();
    curs_set(0);*/

    string v[50];
    int p=0;
    int n=0;

    ifstream f;
    f.open("Personaggio.txt");
    //CONTROLLO CHE datis.txt ESISTA, SE NON ESISTE LO CREO CON UN SET BASE
    if(!f.is_open() || f.peek()==EOF){
        f.close();
        creaFile();
        f.open("Personaggio.txt");
    }

    while(!f.eof()||n<2){   //METTO TUTTE LE RIGHE DEL FILE DENTRO UN VETTORE DI STRINGHE       RICORDA: Riga-->0: Nome; Riga-->1: Punteggio;
        string t;
        getline(f,t);
        v[n]=t;
        n++;
    }
    f.close();

    //misure dello screen
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);

    Menu G(0,1,xMax,yMax);
    Menu S(15,8,105,6);
    Menu K(22,8,105,7);

    //LAVORO SULLA FINESTRA DI SFONDO
    mvwprintw(G.getW(),1,1,"        |||||||     ||     ||  |||        || |||        ||  |||     |||     ||||||||||  ||     || ||||||  |||     |||");
    mvwprintw(G.getW(),2,1,"       |||  ||||   ||     ||  ||||       || ||||       ||   |||   |||      ||||||||||  ||     || ||  |||  |||    ||| ");
    mvwprintw(G.getW(),3,1,"      |||    |||  ||     ||  || ||      || || ||      ||    ||| |||       |||         ||     || ||    ||  |||  |||   ");
    mvwprintw(G.getW(),4,1,"     |||  ||||   ||     ||  ||   ||    || ||   ||    ||     || ||        ||||||||    ||     || ||   ||    || ||      ");
    mvwprintw(G.getW(),5,1,"    |||||||     ||     ||  ||    ||   || ||    ||   ||      |||         ||||||||    ||     || ||||||      |||        ");
    mvwprintw(G.getW(),6,1,"   |||  ||||   ||     ||  ||     ||  || ||     ||  ||      |||         |||         ||     || ||  ||      |||         ");
    mvwprintw(G.getW(),7,1,"  |||    |||  ||     ||  ||      || || ||      || ||      |||         |||         ||     || ||   ||     |||          ");
    mvwprintw(G.getW(),8,1," |||   |||   |||   |||  ||       |||| ||       ||||      |||         |||         |||   ||| ||    ||    |||           ");
    mvwprintw(G.getW(),9,1,"||||||||      |||||    ||        ||| ||        |||      |||         |||           |||||   ||     ||   |||            ");


    mvwprintw(K.getW(), 1,35,"    || ||  ||  ||    ||   |||||");
    mvwprintw(K.getW(), 2,35,"   ||||   ||  ||||  ||  ||| ");
    mvwprintw(K.getW(), 3,35,"  |||    ||  || || ||  ||  ||||");
    mvwprintw(K.getW(), 4,35," || ||  ||  ||  ||||   ||   ||");
    mvwprintw(K.getW(), 5,35,"||  || ||  ||    ||     |||||");


    mvwprintw(K.getW(), 2,12,"Name");
    mvwprintw(K.getW(), 2,80,"Record");

    //PRENDO LE INFO DAL VETTORE PRESO DAI FILE
    /*int tmp=cercaRecord(v,n);*/


    //PROVO A STAMPARE LO SCORE
    string t[2];
    selezionoScore(t);
    while(p<2){
    mvwprintw(K.getW(), 4,p*68+12,"%s ",t[p].c_str());
    p++;
    }
    p=0;

    //wrefresh(menuwinG);
    G.wrW();
    S.wrW();
    K.wrW();

    //lo creo in modo tale da poter usare parole chiave
    //LAVORO SULLA FINESTRA DI SELEZIONE
    keypad(S.getW(), true);
    string choices[3]={"New Game", "Continue", "Exit"};
    int choice;
    int highlight=0;
    stampaConiglio(S.getW(), highlight);

    while(1){
        for(int i=0; i<3; i++){
            if(i==highlight)
                wattron(S.getW(), A_REVERSE);
                if(i==2){
                    mvwprintw(S.getW(), 1, i*45+6, choices[i].c_str());
                }else{
                    mvwprintw(S.getW(), 1, i*45+4, choices[i].c_str());
                }
                wattroff(S.getW(), A_REVERSE);
        }
        choice= wgetch(S.getW());

        switch(choice){
        case KEY_LEFT:
            highlight--;

            if(highlight==-1)
                highlight=2;

            stampaConiglio(S.getW(), highlight);
            break;
        case KEY_RIGHT:
            highlight++;

            if(highlight==3)
                highlight=0;

            stampaConiglio(S.getW(), highlight);
            break;
        default:
            break;
        }
        if(choice==10)
            break;
    }

    //LAVORO SULLA FINESTRA RECORD

    if(choices[highlight] == "Exit"){
        return 0;
    }
    else{
        if(choices[highlight] == "New Game"){

            return 1;
        }
        else{
                if(choices[highlight] == "Continue"){
                return 2;
        }

    }

    //getch();
    }
    return 0;
}
