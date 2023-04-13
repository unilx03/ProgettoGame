#include "map.h"

//#include "Entities/Character.h"
#include "Entities/Hero.h"
//#include "Entities/Enemy.h"
//#include "Entities/BossEnemy.h"

//#include "oggetto.h"

punt_level initializeLevelList(punt_level head)
{
	ifstream inputFile; /* Dichiarazione di tipo */
	char path[100] = "map.txt";
	inputFile.open(path);
	if(!inputFile.fail())
	{
		while (!inputFile.eof())
		{
			punt_level l = new level;
			l->numSpawnEnemies = 0;
			l->numSpawnItems = 0;
			for (int i = 0; i < ROW; i++)
			{
				for (int j = 0; j < COLUMN; j++)
				{
					inputFile >> l->map[j][i];
					if (l->map[j][i] == ENEMYMAPNUMBER) //spawn nemici
					{
						l->spawnEnemies[l->numSpawnEnemies].x = j + 1;
						l->spawnEnemies[l->numSpawnEnemies].y = i + 1;
						l->numSpawnEnemies++;
					}
					else if (l->map[j][i] == ITEMMAPNUMBER) //spawn oggetti
					{
						l->spawnItems[l->numSpawnItems].x = j + 1;
						l->spawnItems[l->numSpawnItems].y = i + 1;
						l->numSpawnItems++;
					}
				}
			}
			head = addLevel(head, l);
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

punt_level addLevel (punt_level node, punt_level liv)
{
	punt_level l = new level;
	
	for (int i = 0; i < COLUMN; i++)
		for (int j = 0; j < ROW; j++)
			l->map[i][j] = liv->map[i][j];
		
	l->numSpawnEnemies = liv->numSpawnEnemies;
	for (int i = 0; i < l->numSpawnEnemies; i++)
	{
		l->spawnEnemies[i].x = liv->spawnEnemies[i].x;
		l->spawnEnemies[i].y = liv->spawnEnemies[i].y;
	}
	l->numSpawnItems = liv->numSpawnItems;
	for (int i = 0; i < l->numSpawnItems; i++)
	{
		l->spawnItems[i].x = liv->spawnItems[i].x;
		l->spawnItems[i].y = liv->spawnItems[i].y;
	}
	
	l->numPositionEnemies = liv->numPositionEnemies;
	for (int i = 0; i < l->numPositionEnemies; i++)
	{
		l->positionEnemies[i].x = liv->positionEnemies[i].x;
		l->positionEnemies[i].y = liv->positionEnemies[i].y;
	}
	l->numPositionItems = liv->numPositionItems;
	for (int i = 0; i < l->numPositionItems; i++)
	{
		l->positionItems[i].x = liv->positionItems[i].x;
		l->positionItems[i].y = liv->positionItems[i].y;
	}
			
	if (node != NULL)
		node->next = l;
	
	l->prec = node;
	l->next = NULL;
	
    return l;
}

punt_level loadMapFromID (punt_level tail, int id)
{
	if (id == 0)
	{
		return tail;
	}
	else
	{
		//return caricaMappaDaID (tail->next, id - 1);
		return loadMapFromID (tail->prec, id - 1);
	}
}

int countLevels(punt_level tail)
{
	if (tail == NULL)
		return 0;
	else
		//return 1 + contaLivelli(tail->next);
		return 1 + countLevels(tail->prec);
}

punt_level nextLevel (punt_level node)
{
	return node->next;
}

punt_level previousLevel (punt_level node)
{
	if (node->prec != NULL)
		return node->prec;
	else
		return node;
}

punt_level generateEnemies (punt_level node)
{
	node->numPositionEnemies = (rand() % 2) + 1;
	for (int i = 0; i < node->numPositionEnemies; i++)
	{
		int randomEnemy = rand() % node->numSpawnEnemies;
		node->positionEnemies[i].x = node->spawnEnemies[randomEnemy].x;
		node->positionEnemies[i].y = node->spawnEnemies[randomEnemy].y;
	}
	return node;
}

punt_level generateItems (punt_level node)
{
	node->numPositionItems = (rand() % 2) + 1;
	for (int i = 0; i < node->numPositionItems; i++)
	{
		int randomItem = rand() % node->numSpawnItems;
		node->positionItems[i].x = node->spawnItems[randomItem].x;
		node->positionItems[i].y = node->spawnItems[randomItem].y;
	}
	return node;
}

void printLevels(punt_level tail)
{
	if (tail != NULL)
	{
		for (int i = 0; i < ROW; i++)
		{
			for (int j = 0; j < COLUMN; j++)
			{
				cout << tail->map[j][i];
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
		printLevels(tail->prec);
	}
}

void drawMap(WINDOW* win, punt_level l)
{
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COLUMN; j++)
		{
			char character = ' ';
			if (l->map[j][i] == 0)
				character = ' ';
			else if (l->map[j][i] == 1)
				character = '_';
			else if (l->map[j][i] == 2)
				character = '|';
			else
				character = ' ';
			mvwprintw(win, i + 1, j + 1, "%c", character);
		}
	}
	
	for (int i = 0; i < l->numPositionEnemies; i++)
	{
		mvwprintw(win, l->positionEnemies[i].y, l->positionEnemies[i].x, "%c", 'N');
	}
	
	for (int i = 0; i < l->numPositionItems; i++)
	{
		mvwprintw(win, l->positionItems[i].y, l->positionItems[i].x, "%c", 'O');
	}
	
	//create_hero(win, 20, 2);

	wrefresh(win);
}