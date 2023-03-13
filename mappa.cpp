#include "mappa.h"

void start()
{
	livello liv = letturaMappa();
	disegnaMappa(liv);
}

livello letturaMappa()
{
	ifstream inputFile; /* Dichiarazione di tipo */
	char path[100] = "mappe.txt";
	inputFile.open(path);
	if(inputFile.fail())
	{
		cout << "\nERROR: could not open file\n";
		exit(1);
	}
	livello liv;

	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 120; j++)
		{
			inputFile >> liv.mappa[j][i];
		}
		cout << endl;
	}

	/*while(!inputFile.eof())
	{
		cout << num << " ";
		inputFile >> num;
	}*/	
	inputFile.close();
	return liv;
}

void disegnaMappa(livello l)
{
	initscr();
	WINDOW* win = newwin(22, 122, 0, 0);
	box(win, 0, 0);
	refresh();
	wrefresh(win);
	
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 120; j++)
		{
			char character = ' ';
			if (l.mappa[j][i] == 0)
				character = ' ';
			else if (l.mappa[j][i] == 1)
				character = '_';
			else if (l.mappa[j][i] == 2)
				character = '|';
			else
				character = ' ';
			mvwprintw(win, i + 1, j + 1, "%c", character);
		}
	}

	wrefresh(win);
	getch();
	endwin();
}