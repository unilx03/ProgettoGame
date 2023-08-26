#include <ncurses/ncurses.h>
#include <string.h>
#include <fstream>
using namespace std;

#define FILENAME "character_stats.txt"

typedef struct {
    char name[50];
    int health;
    int attack;
} Character;

void saveCharacterStats(Character *character) {
    FILE *file = fopen(FILENAME, "w");
    if (file == NULL) {
        mvprintw(10, 10, "Errore nell'apertura del file");
        getch();
        endwin();
        exit(1);
    }
    fprintf(file, "Nome: %s\nVita: %d\nAttacco: %d\n", character->name, character->health, character->attack);
    fclose(file);
}

void printCharacterStats(WINDOW *win) {
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        mvwprintw(win, 1, 1, "Nessuna statistica da leggere");
    } else {
        char line[100];
        int y = 1;
        while (fgets(line, sizeof(line), file)) {
            mvwprintw(win, y, 1, line);
            y++;
        }
        fclose(file);
    }
    wrefresh(win);
}

int main() {
    initscr(); // Inizializza ncurses
    cbreak();
    noecho();

    WINDOW *win = newwin(10, 40, 5, 5);
    box(win, 0, 0);
    refresh();
    wrefresh(win);

    mvprintw(1, 5, "Inserisci il nome del personaggio:");
    char name[50];
    mvgetnstr(2, 2, name, sizeof(name));

    clear();

    Character character;
    strcpy(character.name, name);
    character.health = 100;
    character.attack = 50;

    saveCharacterStats(&character);

    mvprintw(8, 1, "Statistiche salvate. Premi un tasto per leggerle.");
    getch();

    clear();
    refresh();

    WINDOW *displayWin = newwin(10, 40, 5, 5);
    box(displayWin, 0, 0);
    refresh();
    wrefresh(displayWin);

    printCharacterStats(displayWin);

    mvprintw(17, 1, "Premi un tasto per uscire.");
    getch();

    endwin(); //Termina ncurses

    return 0;
}