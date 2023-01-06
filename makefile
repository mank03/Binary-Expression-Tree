all: q1

q1: q1.c
	gcc -Wall -std=c99 -pedantic -o q1 q1.c
