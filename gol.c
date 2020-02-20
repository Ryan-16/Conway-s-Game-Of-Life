void read_in_file(FILE *infile, struct universe *u)
{

    int current_cols;
    int maximum_cols = 512;
    
    u->generation = 1;

    // start with initial 1 row (so 1 char pointers), but we use index 0
    u->rows = 0;
    u->matrix = malloc((u->rows + 1) * sizeof(char *));

    u->matrix[u->rows] = malloc(maximum_cols * sizeof(char *));
    fscanf(infile, "%s", u->matrix[u->rows]);
    u->cols = strlen(u->matrix[u->rows]);
    u->matrix[u->rows] = realloc(u->matrix[u->rows], u->cols * sizeof(char *));

    u->rows ++;
    u->matrix = realloc(u->matrix, (u->rows + 1) * sizeof(char *));
    u->matrix[u->rows] = malloc(u->cols * sizeof(char *));
     
    while (-1 != fscanf(infile, "%s", u->matrix[u->rows])) {
        
        current_cols = strlen(u->matrix[u->rows]);
        if (current_cols != u->cols) {
            // stderror
        }

        else {

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

    for (int = 0; i <= (u->rows); i ++) {
        for (int j = 0; j <= (u->cols); j ++) {
            if (0 == strcmp('*', u->matrix[i][j])) {
                u->total_alive ++;
            }
        }
    }
}

void write_out_file(FILE *outfile, struct universe *u)
{
   
    for (int i = 0; i < (u->rows); i++) {
        fprintf(outfile, "%s\n", u->matrix[i]);
    }
}

int is_alive(struct universe *u, int column, int row)
{
    if (0 == strcmp('*', u->matrix[row][column])) {
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

            else if (0 == strcmp('*', u->matrix[row + row_modifier][column + col_modifier])) {
                
                alive_neighbours ++;
            }
        }
    }

    if (0 == strcmp('*', u->matrix[row][column])) {

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

int will_be_alive_torus(struct universe *u, int column, int row)
{

    int alive_neighbours = 0;

    for (int row_modifier = -1; row_modifier <= 1; row_modifier ++ ) {
        for(int col_modifier = -1; col_modifier <= 1; col_modifier ++) {

            if (col_modifier == 0 && row_modifier == 0) {
                
                // is the current cell
                continue;
            }

            else if (0 == strcmp('*', u->matrix[(row + row_modifier) % (u->rows + 1)]
                        [(column + col_modifier) % (u->rows + 1)])) {
                
                alive_neighbours ++;
            }
        }
    }

    if (0 == strcmp('*', u->matrix[row][column])) {

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
            new_matrix[i][j] = (*rule)(u, column, row);

            if (0 == strcmp('*', u->matrix[i][j])) {
                u->total_alive ++;
            }
        }
    }
    
    // free up old array
    
    for (i = 0; i <= (u->rows); i ++) {
        free(u->matrix[i]);
    }

    free(u->matrix);

    u->matrix = new_matrix;

    u->generation ++;

}

void print_statistics(struct *u)
{
    int number_alive = 0;
    float current_percentage;
    float total_percenrage;

    for (int = 0; i <= (u->rows); i ++) {
        for (int j = 0; j <= (u->cols); j ++) {
            if (0 == strcmp('*', u->matrix[i][j])) {
                number_alive ++;
            }
        }
    }

    current_percentage = number_alive / ((u->rows + 1) * (u->cols + 1));
    
    printf("%.3f", current_percentage);
    printf("%% of cells currently alive\n");

    total_percentage = u->total_alive / ((u->rows + 1) * (u->cols + 1) * generations);

    printf("%.3f", total_percentage);
    printf("%% of cells alive on average\n");

}

