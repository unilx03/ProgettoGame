#include <ncurses.h>
#include <string>
#include <fstream>
#include <iostream>
using namespace std;

int main(int argc, char ** argv){

    //Setup input file
    ifstream menuFile;
    menuFile.open("MenuOptions.txt");
    if(!menuFile){
        cout<<"Impossibile aprire 'MenuOptions.txt'"<<endl;
        exit(1);
    }

    //Prende il numero dei file options
    int count=0;
    int maxOptionLength=0;
    string menuOption;
    while(getline(menuFile, menuOption)){
        count++;
        if(menuOption.length() > maxOptionLength)
            maxOptionLength = menuOption.length();
    }

    //Resetto il file pointer all'inizio del file
    menuFile.clear();
    menuFile.seekg(0, ios::beg);

    //Metto menu Options in un array
    string *menuOptions=new string[count];
    for(int i=0; i<count; i++){
        getline(menuFile, menuOption);
        menuOptions[i]=menuOption;
    }

    //SETTO NCURSES
    initscr();
    noecho();
    cbreak();
    curs_set(0);
    keypad(stdscr, TRUE);//Ci consente di dirottare il tasto freccia e la tastiera


    int input=0;
    int selected=1;

    while(input ! 'q'){//Con q esco
        clear();


        mvprintw(1,12,"Main Menu");
        for(int i=0; i<count; i++){
            mvprintw(i+2,15, menuOptions[i].c_str());
        }
        if(selected > 0 && selected < (count + 1))
            mvprintw(selected+1, 15, maxOptionLength, A_STANDOUT, 1, NULL);
        mvprintw(30, 100, "%i", input);

        refresh();

        //prende l'input dell'utente
        input=getch();
        //Cambio l'opzione scelta
        if(input == KEY_DOWN && selected < count) selected++;
        if(input == KEY_UP && selected > 1) selected--;
    }

    endwin();
    delete [] menuOptions;

}
