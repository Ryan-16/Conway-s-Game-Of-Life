all: gol.o gameoflife.o
	gcc -shared gol.o -o libgol.so -Wall -Wextra -pedantic -std=c11 
	gcc -o gameoflife gameoflife.o -lgol -L. -Wall -Wextra -pedantic -std=c11 

#libgol.so: gol.o
#	gcc -shared gol.o -o libgol.so

gol.o: gol.c gol.h
	gcc -c gol.c -fPIC -Wall -Wextra -pedantic -std=c11

gameoflife.o: gameoflife.c gol.h
	gcc -c gameoflife.c -Wall -Wextra -pedantic -std=c11

clean:
	rm -rf libgol.so gameoflife gol.o gameoflife.o
