FLAGS = -Wall -Wextra -pedantic -std=c11 

all: gol.o gameoflife.o
	gcc -shared gol.o -o libgol.so $(FLAGS)
	gcc -o gameoflife gameoflife.o -lgol -L. $(FLAGS)

gol.o: gol.c gol.h
	gcc -c gol.c -fPIC $(FLAGS)

gameoflife.o: gameoflife.c gol.h
	gcc -c gameoflife.c $(FLAGS)

clean:
	rm -rf libgol.so gameoflife gol.o gameoflife.o
