#include <ncurses.h>
#include <iostream>
using namespace std;
int main() {
    initscr(); // Inizializza ncurses
    cbreak();  // Abilita l'input per carattere (non bufferizzato)
    noecho();  // Non mostrare i caratteri inseriti
    curs_set(1); // Mostra il cursore

    // Crea una finestra per l'input
    WINDOW *win = newwin(10, 40, 5, 5);
    box(win, 0, 0); // Crea una bordatura per la finestra
    refresh();

    // Stampa un prompt
    mvwprintw(win, 1, 1, "Inserisci un nome: ");
    wrefresh(win);

    // Crea un buffer per l'input dell'utente
    char nome[32];
    wgetnstr(win, nome, sizeof(nome));

    // Stampa il nome inserito
    mvwprintw(win, 2, 1, "Hai inserito: %s", nome);
    wrefresh(win);

    // Attendi un input prima di uscire
    getch();

    // Termina ncurses
    endwin();

    return 0;
}


