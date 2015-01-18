#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <ncurses.h>

#define NUMBLOCKS 5

struct thing {
	char ico;
	int pos[2];
};

struct thing player;
struct thing* ply = &player;

struct thing blk[NUMBLOCKS];

struct thing door;
struct thing* dr = &door;

void updatething(struct thing* t, int x, int y) {
	mvaddch(t->pos[1],t->pos[0],' ');
	t->pos[0] += x;
	t->pos[1] += y;
	mvaddch(t->pos[1],t->pos[0],t->ico);
	refresh();
}
int overlap(struct thing* t, int ux, int uy,struct thing b[NUMBLOCKS]) {
	int x = t->pos[0]+ux;
	int y = t->pos[1]+uy;
	for (int i = 0; i < NUMBLOCKS; i++) {
		if (b[i].pos[0] == x) {
			if (b[i].pos[1] == y) {
				return 1;
			}
		}
	}
	return 0;
}
void end() {
	printf("Thanks for playing!\n");
	exit(0);

}
// drop player
void gravity() {
	if(ply->pos[0] == dr->pos[0] && ply->pos[1] == dr->pos[1]) {
		endwin();
		printf("You Win!");
		end();
	}
	if(!overlap(ply,0,1,blk)) {
		updatething(ply,0,1);
	}
}

int main () {
	srand(time(NULL));
	memset(ply,0,sizeof(struct thing));

	memset(blk,0,sizeof(blk));

	memset(dr,0,sizeof(struct thing));

	int config = open("config.txt",O_RDONLY);
	char cfg[3];
	int er = read(config,cfg,3);
	if (er < 3) {
		perror("Failed to read config");
		exit(0);
	}
	ply->ico = cfg[0];
	dr->ico = cfg[2];
	for (int i = 0; i < NUMBLOCKS; i++) {
		blk[i].ico = cfg[1];
		//setup location of blocks while we are at it
		printf("%d\n%d\n%d\n",rand(),LINES,COLS);
		blk[i].pos[0] = (int)(rand()/LINES);
		blk[i].pos[1] = (int)(rand()/COLS);
	}
	dr->pos[0] = rand()/LINES;
	dr->pos[1] = rand()/COLS;
	initscr();
	cbreak();
	updatething(ply,COLS/2,LINES/2);

	//draw blocks
	for (int i = 0; i < NUMBLOCKS; i++) {
		updatething(&blk[i],0,0);
	}
	//setup gravity
	signal(SIGALRM,gravity);
	alarm(1);
	char inp;
	for(;;inp=getch()) {
		switch(inp) {
			case 'w':
				updatething(ply,0,-1);
				break;
			case 'a':
				updatething(ply,-1,0);
				break;
			case 's':
				updatething(ply,0,1);
				break;
			case 'd':
				updatething(ply,1,0);
				break;
			case 'g':
				endwin();
				end();
		}
	}
}


