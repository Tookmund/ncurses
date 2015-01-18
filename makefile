FLAGS := -Wall -Werror -g -std=c99
all: main platform

main: main.c
	gcc $^ -lncurses -o main

platform: platform.c
	gcc $^ -lncurses -o platform $(FLAGS)
