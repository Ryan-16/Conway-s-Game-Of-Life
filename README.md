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
