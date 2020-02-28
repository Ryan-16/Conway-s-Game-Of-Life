FLAGS = -Wall -Wextra -pedantic -std=c11 -ggdb3 

all: gameoflife.o libgol.so
	gcc -o gameoflife gameoflife.o -lgol -L. $(FLAGS)

libgol.so: gol.o
	gcc -shared gol.o -o libgol.so $(FLAGS)

gol.o: gol.c gol.h
	gcc -c gol.c -fPIC $(FLAGS)

gameoflife.o: gameoflife.c gol.h
	gcc -c gameoflife.c $(FLAGS)

clean:
	rm -rf libgol.so gameoflife gol.o gameoflife.o
