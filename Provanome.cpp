#include <ncurses.h>
#include <iostream>
using namespace std;

int main() {
    initscr();
    cbreak();
    keypad(stdscr, TRUE); // Abilita il keypad per tastiere speciali (es. F1, F2)
    curs_set(1);

    // Crea una finestra per l'input
    WINDOW *win = newwin(10, 40, 5, 5);
    box(win, 0, 0);
    refresh();

    // Stampa un prompt
    mvwprintw(win, 1, 1, "Inserisci un nome: ");
    wrefresh(win);

    // Crea un buffer per l'input dell'utente
    char nome[32];
    echo(); // Abilita l'eco (visualizza ciò che viene digitato)
    mvwgetnstr(win, 2, 1, nome, sizeof(nome)); // Mostra ciò che l'utente digita
    noecho(); // Disabilita l'eco

    // Stampa il nome inserito
    mvwprintw(win, 3, 1, "Hai inserito: %s", nome);
    wrefresh(win);

    // Attendi un input prima di uscire
    getch();

    endwin();

    return 0;
}
