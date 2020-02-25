all: gol.o gameoflife.c
	LD_LIBRARY_PATH=`pwd`
	export LB_LIBRARY_PATH
	gcc -shared gol.o -o libgol.so
	gcc -o gameoflife gameoflife.c -lgol -L.

#libgol.so: gol.o
#	gcc -shared gol.o -o libgol.so

gol.o: gol.c gol.h
	gcc -c gol.c -fPIC -Wall -Wextra -pedantic -std=c11

#gameoflife.o: gameoflife.c gol.h
#	gcc -c gameoflife.c -Wall -Wextra -pedantic -std=c11

clean:
	rm -rf libgol.so gameoflife gol.o gameoflife.o
