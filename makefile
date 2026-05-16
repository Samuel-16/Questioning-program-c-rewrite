all: program

program: main.c
	gcc main.c -o Simple\ questioning\ program -Os -Wall -Werror
