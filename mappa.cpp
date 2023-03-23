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
	punt_livello l = new livello;
	
	for (int i = 0; i < 80; i++)
		for (int j = 0; j < 20; j++)
			l->mappa[i][j] = liv->mappa[i][j];
		
	l->numSpawnNemici = liv->numSpawnNemici;
	for (int i = 0; i < l->numSpawnNemici; i++)
	{
		l->spawnNemici[i].x = liv->spawnNemici[i].x;
		l->spawnNemici[i].y = liv->spawnNemici[i].y;
	}
	l->numSpawnOggetti = liv->numSpawnOggetti;
	for (int i = 0; i < l->numSpawnOggetti; i++)
	{
		l->spawnOggetti[i].x = liv->spawnOggetti[i].x;
		l->spawnOggetti[i].y = liv->spawnOggetti[i].y;
	}
	
	l->numPosizioneNemici = liv->numPosizioneNemici;
	for (int i = 0; i < l->numPosizioneNemici; i++)
	{
		l->posizioneNemici[i].x = liv->posizioneNemici[i].x;
		l->posizioneNemici[i].y = liv->posizioneNemici[i].y;
	}
	l->numPosizioneOggetti = liv->numPosizioneOggetti;
	for (int i = 0; i < l->numPosizioneOggetti; i++)
	{
		l->posizioneOggetti[i].x = liv->posizioneOggetti[i].x;
		l->posizioneOggetti[i].y = liv->posizioneOggetti[i].y;
	}
			
	if (nodo != NULL)
		nodo->next = l;
	
	l->prec = nodo;
	l->next = NULL;
	
    return l;
}

punt_livello caricaMappaDaID (punt_livello tail, int id)
{
	if (id == 0)
	{
		return tail;
	}
	else
	{
		//return caricaMappaDaID (tail->next, id - 1);
		return caricaMappaDaID (tail->prec, id - 1);
	}
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

punt_livello generaNemici (punt_livello nodo)
{
	nodo->numPosizioneNemici = (rand() % 2) + 1;
	for (int i = 0; i < nodo->numPosizioneNemici; i++)
	{
		int randomNemico = rand() % nodo->numSpawnNemici;
		nodo->posizioneNemici[i].x = nodo->spawnNemici[randomNemico].x;
		nodo->posizioneNemici[i].y = nodo->spawnNemici[randomNemico].y;
	}
	return nodo;
}

punt_livello generaOggetti (punt_livello nodo)
{
	nodo->numPosizioneOggetti = (rand() % 2) + 1;
	for (int i = 0; i < nodo->numPosizioneOggetti; i++)
	{
		int randomOggetto = rand() % nodo->numSpawnOggetti;
		nodo->posizioneOggetti[i].x = nodo->spawnOggetti[randomOggetto].x;
		nodo->posizioneOggetti[i].y = nodo->spawnOggetti[randomOggetto].y;
	}
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
	
	for (int i = 0; i < l->numPosizioneNemici; i++)
	{
		mvwprintw(win, l->posizioneNemici[i].y, l->posizioneNemici[i].x, "%c", 'N');
	}
	
	for (int i = 0; i < l->numPosizioneOggetti; i++)
	{
		mvwprintw(win, l->posizioneOggetti[i].y, l->posizioneOggetti[i].x, "%c", 'O');
	}
	
	mvwprintw(win, 20, 1, "%c",'S');

	wrefresh(win);
}