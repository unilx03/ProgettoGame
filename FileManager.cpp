#include "FileManager.h"

//Scrive su file le statistiche dell'eroe
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

//Refresh del menù
void Menu::wrW(){
    box(this->getW(), 0, 0);
    wrefresh(this->getW());
}

//Stampa la skin dell'eroe all'interno del menù
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

//Seleziona l'ultimo score ottenuto per visualizzarlo nel menù
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

//Crea il menù principale. Ritorna la scelta selezionata dall'utente
int create_menu(){
    string v[50];
    int p=0;
    int n=0;

    ifstream f;
    f.open("Personaggio.txt");
    //CONTROLLO CHE datis.txt ESISTA, SE NON ESISTE LO CREO CON UN SET BASE
    if(!f.is_open() || f.peek()==EOF){
        f.close();
        creaFileStat();
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
    mvwprintw(K.getW(), 2,80,"Last Score");

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

//Crea finestra dove vengono visualizzarte le statistiche correnti dell'eroe durante la partita
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

        if(i==5){
            mvwprintw(menuwinG, (i-1)*5, n*14+9, "%s ",t.c_str());
            n++;
        }
        else
            mvwprintw(menuwinG, (i-1)*5, n*14+6,"%s ",t.c_str());

        n++;
        }
    }
    f.close();

    wrefresh(menuwinG);
}

//Schermata visualizzata quando avviene un game over
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

//Richiamata quando l'utente decide di iniziare una nuova partita, fa inserire il nome del nuovo player
string inseriscinome() {

    // Crea una finestra per l'input
    WINDOW *namewin = newwin(22, 162, 2, 5);
    box(namewin, 0, 0);
    refresh();

    // Stampa un prompt
    mvwprintw(namewin, 1, 1, "Inserisci un nome: ");
    wrefresh(namewin);

    // Crea un buffer per l'input dell'utente
    char nome[32];
    echo(); // Abilita l'eco (visualizza ciò che viene digitato)
    mvwgetnstr(namewin, 2, 1, nome, sizeof(nome)); // Mostra ciò che l'utente digita
    noecho(); // Disabilita l'eco

    string str(nome, sizeof(nome) / sizeof(nome[0]));

    //saveCharacterStats(str,0, 25, 1, 0, 0, 0, 1, 0);

    wrefresh(namewin);

    return str;
}