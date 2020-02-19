//#include<stdio.h>
//#include<stdlib.h>
//#include"gol.h"
//#include<string.h>

void read_in_file(FILE *infile, struct universe *u)
{

    int current_cols;
    int maximum_cols = 512;

    // start with initial 1 row (so 1 char pointers)
    u->rows = 1;
    u->matrix = malloc(u->rows * sizeof(char *));

    u->matrix[u->rows - 1] = malloc(maximum_cols * sizeof(char *));
    u->cols = fscanf(infile, "%s", u->matrix[u->rows - 1]);
    u->matrix[u->rows - 1] = realloc(u->matrix[u->rows - 1], u->cols * sizeof(char *));

    u->rows ++;
    u->matrix = realloc(u->matrix, u->rows * sizeof(char *));
    u->matrix[u->rows - 1] = malloc(u->cols * sizeof(char *));
     
    while (-1 != (current_cols = fscanf(infile, "%s", u->matrix[u->rows - 1]))) {

        if (current_cols != u->cols) {
            // stderror
        }

        else {

            u->rows ++;
            u->matrix = realloc(u->matrix, u->rows * sizeof(char *));
            u->matrix[u->rows - 1] = malloc(u->cols * sizeof(char *));
        }
    }

    // free up EOF memory
    free(u->matrix[u->rows - 1]);
    u->rows --;
    u->matrix = realloc(u->matrix, u->rows * sizeof(char *));

/*    printf("\n\n");

    for (int i = 0; i < (u->rows); i++) {

        printf("%s\n", u->matrix[i]);
    } */
}

void write_out_file(FILE *outfile, struct universe *u)
{
   
    for (int i = 0; i < (u->rows); i++) {
        fprintf(outfile, "%s\n", u->matrix[i]);
    }
}

int is_alive(struct universe *u, int column, int row)
{
    if (0 == strcmp(u->alive, u->matrix[row][column])) {
        return 1;
    }

    else {
        return 0;
    }
}

int will_be_alive(struct universe *u, int column, int row)
{   
    int alive_neighbours = 0;

    for (int row_modifier = -1; row_modifier <= 1; row_modifier ++ ) {
        for(int col_modifier = -1; col_modifier <= 1; col_modifier ++) {
            
            if (row + row_modifier < 0 || row + row_modifier > u->rows ||
                column + col_modifier < 0 || column + col_modifier > u->cols ||) {
                
                // out of universe
                continue;
            }

            else if (col_modifier == 0 && row_modifier == 0) {
                
                // is the current cell
                continue;
            }

            else if (0 == strcmp(u->alive, u->matrix[row + row_modifier][column + col_modifier])) {
                
                alive_neighbours ++;
            }
        }
    }

    if (0 == strcmp(u->alive, u->matrix[row][column])) {

        // alive

        if (alive_neighbours == 2 || alive_neighbours == 3) {

            return 1;
        }
    }

    else {

        // dead

        if (alive_neighbours == 3) {

            return 1;
        }
    }

    return 0;

}


/*
int main() {

    struct universe v;
    read_in_file(stdin, &v);
    
    return 0;
}*/
