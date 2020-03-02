#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include"gol.h"

void read_in_file(FILE *infile, struct universe *u)
{
    // load chars into temp, and then into struct, checking for errors

    int maximum_cols = 512;
    int count = 0;
    char character;
    bool first_row = true;
    u->generation = 1;
    
    // start with 1 row and dynamically allocate memory (note count starting at 0)
    u->rows = 0;
    u->cols = maximum_cols;
    u->total_alive = 0;
    u->matrix = malloc((u->rows + 1) * sizeof(char *));

    // assign first rows memory
    u->matrix[u->rows] = malloc(maximum_cols * sizeof(char *));

    while (-1 != fscanf(infile, "%c", &character)) {
        if (character == '\n') {
            if (count == 0) {
                fprintf(stderr, "Invalid new line\n");
                exit(1);
            }
            if (count > maximum_cols) {
                fprintf(stderr, "Too many columns\n");
                exit(1);
            }
            if (first_row) {
                u->cols = count;
                
                u->matrix[u->rows] = realloc(u->matrix[u->rows], (u->cols) * sizeof(char *));
                first_row = false;
            }
            else if (count != u->cols) {
                fprintf(stderr, "Inconsistent number of columns\n");
                exit(1);
            }
            count = 0;
            u->rows ++;
            u->matrix = realloc(u->matrix, (u->rows + 1) * sizeof(char *));
            u->matrix[u->rows] = malloc(u->cols * sizeof(char*));
        }
        else{
            if (character != '*' && character != '.') {
                fprintf(stderr, "Input contains invalid characters\n");
                exit(1);
            }
            if (count > u->cols) {
                fprintf(stderr, "Number of columns inconsistant\n");
                exit(1);
            } 
            u->matrix[u->rows][count] = character;
            if (is_alive(u, count, u->rows)) {
                u->total_alive ++;
            } 
            count ++;
        }
    }

    if (character != '\n') {
        fprintf(stderr, "\nInput file did not end with a line break\n");
        exit(1);
    }

    free(u->matrix[u->rows]);
    u->rows --;
    u->cols --;
    u->matrix = realloc(u->matrix, (u->rows + 1) * sizeof(char*));
    
}

void write_out_file(FILE *outfile, struct universe *u)
{ 
    for (int i = 0; i <= (u->rows); i++) {
        for (int j = 0; j <= (u->cols); j++) {
            fprintf(outfile, "%c", u->matrix[i][j]);
         }
         fprintf(outfile, "\n");
    }
}

int is_alive(struct universe *u, int column, int row)
{
    if (column > u->cols || row > u->rows || column < 0 || row < 0) {
        fprintf(stderr, "Row/col out of universe (is_alive) \n");
        exit(1);
    }

    char alive = '*';
    if (alive == u->matrix[row][column]){
        return 1;
    }

    else {
        return 0;
    }
}

int will_be_alive(struct universe *u, int column, int row)
{  
    if (column > u->cols || row > u->rows || column < 0 || row < 0) {
        fprintf(stderr, "Row/col out of universe (will_be_alive) \n");
        exit(1);
    }

    int alive_neighbours = 0;

    for (int row_modifier = -1; row_modifier <= 1; row_modifier ++ ) {
        for(int col_modifier = -1; col_modifier <= 1; col_modifier ++) {
            
            if ((long)row + (long)row_modifier < 0 || (long)row + (long)row_modifier > (long)u->rows ||
                (long)column + (long)col_modifier < 0 || (long)column + (long)col_modifier > (long)u->cols) {
                // out of universe
                continue;
            }
            else if (col_modifier == 0 && row_modifier == 0) {
                // is the current cell
                continue;
            }
            else if (is_alive(u, column + col_modifier, row + row_modifier)) {
                alive_neighbours ++;
            }
        }
    }

    if (is_alive(u, column, row)) {
        if (alive_neighbours == 2 || alive_neighbours == 3) {
            return 1;
        }
    }
    else {
        if (alive_neighbours == 3) {
            return 1;
        }
    }

    return 0;

}

int will_be_alive_torus(struct universe *u, int column, int row)
{

    if (column > u->cols || row > u->rows || column < 0 || row < 0) {
        fprintf(stderr, "Row/col out of universe (torus) \n");
        exit(1);
    }

    int alive_neighbours = 0;

    for (int row_modifier = -1; row_modifier <= 1; row_modifier ++ ) {
        for(int col_modifier = -1; col_modifier <= 1; col_modifier ++) {
            if (col_modifier == 0 && row_modifier == 0) {           
                // is the current cell
                continue;
            }
            else if (is_alive(u, (((long)column + (long)col_modifier) + ((long)u->cols + 1)) % ((long)u->cols + 1), (((long)row + (long)row_modifier) + ((long)u->rows + 1)) % ((long)u->rows + 1))) {
                alive_neighbours ++;
            }
        }
    }
    if (is_alive(u, column, row)) {
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

void evolve(struct universe *u, int (*rule) (struct universe *u, int column, int row))
{
    char new_matrix[u->rows + 1][u->cols + 1];
    for (int i = 0; i <= (u->rows); i ++) {
        for (int j = 0; j <= (u->cols); j ++) {
            if (rule(u, j, i)) {
                new_matrix[i][j] = '*';
                u->total_alive ++;
            }
            else {
                new_matrix[i][j] = '.';
            }
        }
    }

    for (int i = 0; i <= (u->rows); i ++) {

        memcpy(u->matrix[i], new_matrix[i], u->cols + 1);
    }

    u->generation ++;
}

void print_statistics(struct universe *u)
{
    int number_alive = 0;
    float current_percentage;
    float total_percentage;

    for (int i = 0; i <= (u->rows); i ++) {
        for (int j = 0; j <= (u->cols); j ++) {
            if (is_alive(u, j, i)) {
                number_alive ++;
            }
        }
    }

    current_percentage = ((double) number_alive / ((u->rows + 1) * (u->cols + 1))) * 100;
    printf("%.3f", current_percentage);
    printf("%% of cells currently alive\n");
    
    total_percentage = ((double) u->total_alive / ((u->rows + 1) * (u->cols + 1) * u->generation)) * 100;
    printf("%.3f", total_percentage);
    printf("%% of cells alive on average\n");

}

