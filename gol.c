#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include"gol.h"

void read_in_file(FILE *infile, struct universe *u)
{

    int current_cols;
    int maximum_cols = 512;
    char buffer[513];
    
    u->generation = 1;

    // start with initial 1 row (so 1 char pointers), but we use index 0
    u->rows = 0;
    u->matrix = malloc((u->rows + 1) * sizeof(char *));

    u->matrix[u->rows] = malloc(maximum_cols * sizeof(char *));
    fscanf(infile, "%s", buffer);

    if (strlen(buffer) > 512 || strlen(buffer) < 1) {
        fprintf(stderr, "Invalid universe input\n");
        exit(1);
    }


    memcpy(u->matrix[u->rows], buffer, strlen(buffer));
    u->cols = strlen(u->matrix[u->rows]);
    
    for (int i = 0; i < u->cols; i ++) {
        if (u->matrix[u->rows][i] != '*' && u->matrix[u->rows][i] != '.') {
            fprintf(stderr, "Input contains invalid characters\n");
            exit(1);
        }
    }

    u->matrix[u->rows] = realloc(u->matrix[u->rows], u->cols * sizeof(char *));

    u->rows ++;
    u->matrix = realloc(u->matrix, (u->rows + 1) * sizeof(char *));
    u->matrix[u->rows] = malloc(u->cols * sizeof(char *));

    while (-1 != fscanf(infile, "%s", buffer)) {
        current_cols = strlen(buffer);
        if (current_cols != u->cols || current_cols < 1) {
            fprintf(stderr, "Invalid universe input\n");
            exit(1);
        }

        else {
           
            memcpy(u->matrix[u->rows], buffer, strlen(buffer));
            for (int i = 0; i < u->cols; i ++) {
               // printf("%c", u->matrix[u->rows][i]);
                if (u->matrix[u->rows][i] != '*' && u->matrix[u->rows][i] != '.') {
                    fprintf(stderr, "Input contains invalid characters\n");
                    exit(1);
                }
            }

            u->rows ++;
            u->matrix = realloc(u->matrix, (u->rows + 1) * sizeof(char *));
            u->matrix[u->rows] = malloc(u->cols * sizeof(char *));
        }
    }

    // free up EOF memory
    free(u->matrix[u->rows]);
    u->rows --;
    u->matrix = realloc(u->matrix, (u->rows + 1) * sizeof(char *));

    u->cols --;

    // now update the total alive
    
    u->total_alive = 0;

    for (int i = 0; i <= (u->rows); i ++) {
        for (int j = 0; j <= (u->cols); j ++) {
            if (is_alive(u, j, i)) {
                u->total_alive ++;
            }
        }
    }
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
    int alive_neighbours = 0;

    for (int row_modifier = -1; row_modifier <= 1; row_modifier ++ ) {
        for(int col_modifier = -1; col_modifier <= 1; col_modifier ++) {
            
            if (row + row_modifier < 0 || row + row_modifier > u->rows ||
                column + col_modifier < 0 || column + col_modifier > u->cols) {
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

    int alive_neighbours = 0;

    for (int row_modifier = -1; row_modifier <= 1; row_modifier ++ ) {
        for(int col_modifier = -1; col_modifier <= 1; col_modifier ++) {
            if (col_modifier == 0 && row_modifier == 0) {           
                // is the current cell
                continue;
            }
            else if (is_alive(u, ((column + col_modifier) + (u->cols + 1)) % (u->cols + 1), ((row + row_modifier) + (u->rows + 1)) % (u->rows + 1))) {
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
    char **new_matrix;

    new_matrix = malloc((u->rows + 1) * sizeof(char *));
    
    for (int i = 0; i <= (u->rows); i ++) {
        new_matrix[i] = malloc((u->cols) * sizeof(char *));
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
    // free up old array
    for (int i = 0; i <= (u->rows); i ++) {
        free(u->matrix[i]);
    }

    free(u->matrix);
    u->matrix = new_matrix;
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

    current_percentage = ((float) number_alive / ((u->rows + 1) * (u->cols + 1))) * 100;
    printf("%.3f", current_percentage);
    printf("%% of cells currently alive\n");
    
    total_percentage = ((float) u->total_alive / ((u->rows + 1) * (u->cols + 1) * u->generation)) * 100;
    printf("%.3f", total_percentage);
    printf("%% of cells alive on average\n");

}

