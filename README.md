# Conway-s-Game-Of-Life

An implementation of Conway's Game of Life in C using shared libraries

## About

Conway’s Game of Life is a cellular automaton invented by John Conway in 1970. The game world consists
of an infinite two-dimensional grid of cells, each of which is either “dead” or “alive” in each “generation.”
The game comes with a “rule” that explains how to calculate the state of a cell in the next generation.
To find (“evolve”) the next generation, each cell looks at the eight cells next to it (vertically, horizontally
or diagonally), checks which of these are dead or alive in the current generation and then uses this rule to
decide whether the cell should be alive in the next generation. There are various rules one can use to evolve
the next generation. Conway’s rule is as follows:
1. If a cell is alive in the current generation and exactly two or three of its neighbours are alive, then it
will be alive in the next generation.
2. If a cell is dead in the current generation and exactly three of its neighbours are alive, then it will be
alive in the next generation.
3. Otherwise, the cell will be dead in the next generation.

‘*’ represents a live cell and ‘.’ represents a dead cell

## Usage

As this program uses a dynamically-linked library, run: 
`export LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH`
in the directory this repository is cloned to.

`make clean`
`make all`
`./gameoflife`

## Options
• -i input_filename to specify that the initial generation of the universe should be read from a file. If
this option is not specified, the user can type in the input via stdin
• -o output_filename to specify a file into which the final generation should be output. If this option
is not specified, the final generation is output on the screen.
• -g number_of_generations to specify the number of new generations for which the game should be
run. (default is 5).
• -s to print statistics after the final generation has been output.
• -t to use the torus topology for the rule. If this is not specified, use the rule for cells outside the
universe being permanently dead.

## Input files
In any valid file, there will be at most 512 columns; the number of rows is not
limited.

e.g. a valid file `test.txt` could contain:
....................
....................
....................
....................
...*................
....*...............
..***...............
....................
....................
....................
....................
....................
....................
....................
....................
....................
....................
....................
....................
....................
