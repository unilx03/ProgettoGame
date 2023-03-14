#include "mappa.h"

punt_livello inizializzaListaLivelli(punt_livello head)
{
	ifstream inputFile; /* Dichiarazione di tipo */
	char path[100] = "mappe.txt";
	inputFile.open(path);
	if(!inputFile.fail())
	{
		while (!inputFile.eof())
		{
			punt_livello l = new livello;
			l->numSpawnNemici = 0;
			l->numSpawnOggetti = 0;
			for (int i = 0; i < 20; i++)
			{
				for (int j = 0; j < 80; j++)
				{
					inputFile >> l->mappa[j][i];
					if (l->mappa[j][i] == 3) //spawn nemici
					{
						l->spawnNemici[l->numSpawnNemici].x = j + 1;
						l->spawnNemici[l->numSpawnNemici].y = i + 1;
						l->numSpawnNemici++;
					}
					else if (l->mappa[j][i] == 5) //spawn oggetti
					{
						l->spawnOggetti[l->numSpawnOggetti].x = j + 1;
						l->spawnOggetti[l->numSpawnOggetti].y = i + 1;
						l->numSpawnOggetti++;
					}
				}
			}
			head = aggiungiLivello(head, l);
		}
		head = head->next; //il ciclo while crea un livello vuoto in più in testa
	}
	
	inputFile.close();
	return head;
}

punt_livello aggiungiLivello (punt_livello head, punt_livello liv) //push di una pila
{
	liv->next = head;
	head = liv;
	return head;
}

void stampaLivelli(punt_livello head)
{
	if (head != NULL)
	{
		for (int i = 0; i < 20; i++)
		{
			for (int j = 0; j < 80; j++)
			{
				cout << head->mappa[j][i];
			}
		}
		cout << endl << endl;
		stampaLivelli(head->next);
	}
}

void disegnaMappa(WINDOW* win, punt_livello l)
{
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 80; j++)
		{
			char character = ' ';
			if (l->mappa[j][i] == 0)
				character = ' ';
			else if (l->mappa[j][i] == 1)
				character = '_';
			else if (l->mappa[j][i] == 2)
				character = '|';
			else
				character = ' ';
			mvwprintw(win, i + 1, j + 1, "%c", character);
		}
	}
	
	int randomNemico = rand() % l->numSpawnNemici;
	mvwprintw(win, l->spawnNemici[randomNemico].y, l->spawnNemici[randomNemico].x, "%c", 'N');
	
	int randomOggetto = rand() % l->numSpawnOggetti;
	mvwprintw(win, l->spawnOggetti[randomOggetto].y, l->spawnOggetti[randomOggetto].x, "%c", 'O');
	
	mvwprintw(win, 20, 1, "%c",'S');

	wrefresh(win);
}