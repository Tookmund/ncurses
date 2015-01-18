#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <time.h>

char ply = '@';
int main (int argc, char* argv[]) {
	initscr();
	noecho();
	cbreak();

	int pos[2] = {40,40}; // assuming 80x80 terminal
	mvaddch(pos[1],pos[0],ply);
	//add random enemy
	char inp;
	for(;;inp = getch()) {
		// delete current onscreen player
		mvaddch(pos[1],pos[0],' ');
		switch(inp) {
			case 'w':
				// go up one, reverse of common sense
				pos[1] -= 1;
				break;
			case 'a':
				//go left 1
				pos[0] -= 1;
				break;
			case 'd':
				//go right 1
				pos[0] += 1;
				break;
			case 's':
				//go down 1, reverse of common sense
				pos[1] += 1;
				break;
			default:
				break;
		}
		mvaddch(pos[1],pos[0],ply);
	}
	endwin();
	return 0;
}
