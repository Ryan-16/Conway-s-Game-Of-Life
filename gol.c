#include<stdio.h>
#include<stdlib.h>
#include"gol.h"

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

int main() {

    struct universe v;
    read_in_file(stdin, &v);
    
    return 0;
}
