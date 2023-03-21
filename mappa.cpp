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
			head = aggiungiLivelloDopo(head, l);
		}
		//head = head->next; //il ciclo while crea un livello vuoto in più in testa
		head = head->prec; //il ciclo while crea un livello vuoto in più in fondo
		head->next = NULL;
	}
	
	inputFile.close();
	return head;
}

/*punt_livello aggiungiLivelloTesta (punt_livello head, punt_livello liv)
{
	liv->prec = NULL;
	liv->next = head;
	head = liv;
	return head;
}*/

punt_livello aggiungiLivelloDopo (punt_livello nodo, punt_livello liv)
{
	if (nodo != NULL)
		nodo->next = liv;
	
	liv->prec = nodo;
	liv->next = NULL;
	
    return liv;
}

punt_livello caricaMappaDaID (punt_livello tail, int id)
{
	if (id == 0)
		return tail;
	else
		//return caricaMappaDaID (tail->next, id - 1);
		return caricaMappaDaID (tail->prec, id - 1);
}

int contaLivelli(punt_livello tail)
{
	if (tail == NULL)
		return 0;
	else
		//return 1 + contaLivelli(tail->next);
		return 1 + contaLivelli(tail->prec);
}

punt_livello livelloSuccessivo (punt_livello nodo)
{
	return nodo->next;
}

punt_livello livelloPrecedente (punt_livello nodo)
{
	if (nodo->prec != NULL)
		return nodo->prec;
	else
		return nodo;
}

void stampaLivelli(punt_livello tail)
{
	if (tail != NULL)
	{
		for (int i = 0; i < 20; i++)
		{
			for (int j = 0; j < 80; j++)
			{
				cout << tail->mappa[j][i];
			}
			cout << endl;
		}
		
		if (tail->prec != NULL)
			cout << "Ha precedente" << endl;
		else
			cout << "Non ha precedente" << endl;
		
		if (tail->next != NULL)
			cout << "Ha successivo" << endl;
		else
			cout << "Non ha successivo" << endl;
		
		cout << endl << endl;
		//stampaLivelli(tail->next);
		stampaLivelli(tail->prec);
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