//============================================================================
// Name        : ProgettoGame.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "mappa.h"

int main() {
	//initialize screen
		initscr();
		//hide input
		noecho();

		//ctrl+c to exit
		cbreak();
		/*
		//ctrl+c is taken as characters and not command
		raw();
		*/

		/*
		//move cursor in a specific position (y, x)
		//mvprintw(y, x, string): move then printfw
		move(5, 0);

		//getch: wait for user input, return key as integer
		int key = getch();

		//print string in a window (printf format)
		printw("%d", key);
		getch();
		*/

		int height, width, start_x, start_y;

		height = 20;
		width = 60;
		start_x = 5;
		start_y = 2;


		//create a new window (height, width, start_y, stat_x)
		WINDOW* win = newwin(height, width, start_y, start_x);


		//refresh screen to match what's in memory
		refresh();

		//create border around window (window*, character as right-left border, character as top-down border)
		//can cast a char to get int value
		box(win, 0, 0);

		//output on window (window*, char*) where the cursor is
		wprintw(win, "Box");
		//move + wprintw
		mvwprintw(win, 1, 2, "Info");

		wrefresh(win);

		/*
		//if true, can find pressed character as KEY_CHARACTER
		keypad(win, true);

		//get user input
		//when using wgetch the window is refreshed before waiting for input
		int c = wgetch(win);
		mvwprintw(win, 5, 2, "You pressed %d", c);

		//when making changes in memory, these are shown only after refresh
		//refresh window (window*)
		wrefresh(win);
		*/

		/*
		//stdscr: terminal window
		int y, x, yBeg, xBeg, yMax, xMax;
		//get cursor coordinates (window*, variable to put y value, variable to put x value)
		getyx(win, y, x);
		//get coordinates of the cursor at the beginning (window*, variable to put y value, variable to put x value)
		getbegyx(win, yBeg, xBeg);
		//get height and width of the window
		getmaxyx(win, yMax, xMax);
		 */

		/*
		//activate attribute (change text format)
		attron(A_NORMAL);
		//deactivate attribute
		attroff(A_NORMAL);

		//if terminal can change foreground color
		if (!has_colors())
			return -1;
		else
		{
			start_color();
			//create pair of foreground-background colors (id, foreground, background)
			init_pair(0, COLOR_GREEN, COLOR_BLACK);
			//to set color COLOR_PAIR(id)
			attron(COLOR_PAIR(0));
		}

		//if systema can customize color
		if (!can_change_color())
			return -1;
		else
		{
			//as parameter RGB from 0 to 999
			init_color(COLOR_CYAN, 560, 305, 194);
		}
		 */

		/*
		//clear screen
		clear();

		//ends ncurses
		endwin();
		*/

		//creating menu
		/*WINDOW* menu = newwin(height, width, start_y, start_x);
		box(menu, 0, 0);
		refresh();
		wrefresh(menu);

		keypad(menu, true);
		char* choices[3] = {"Start", "Help", "Exit"};
		int choice;
		int highlight = 0;

		bool loop = true;
		while (loop)
		{
			for (int i = 0; i < 3; i++)
			{
				//set attribute to highlighted option
				if (i == highlight)
					wattron(menu, A_REVERSE);
				else
					wattroff(menu, A_REVERSE);
				mvwprintw(menu, i+1, 1, choices[i]);
			}

			choice = wgetch(menu);
			if (choice == KEY_UP)
				highlight--;
			else if (choice == KEY_DOWN)
				highlight++;
			else if (choice == 10) //return
				loop = false;

			if (highlight < 0)
				highlight = 0;
			else if (highlight > 2)
				highlight = 2;
		}

		clear();*/

		getch();
		endwin();
}
