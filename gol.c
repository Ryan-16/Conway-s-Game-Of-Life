void read_in_file(FILE *infile, struct universe *u)
{
    // work out number of rows and cells
    // dynamically allocate the memory
    // populate the matrix

    // maximum length of any given row is 512, so set first row length to 512 then realloc it once know length
    // start with 1 row and realloc every time

    int current_cols;
    int maximum_cols;

    // start with 2 rows (so 2 char pointers)
    u.rows = 2;
    u.matrix = malloc(u.rows * sizeof(char *));

    u.matrix[0] = malloc(maximum_cols * sizeof(char *));

    current_cols = fscanf(infile, "%c", u.matrix[0]);
    u.cols = current_cols;

    u.matrix[0] = realloc(u.matrix[0], u.cols * sizeof(char *));
    u.matrix[1] = malloc(u.cols * sizeof(char *));
    
    while (EOF != (current_cols = fscanf(infile, "%c", u.matrix[u.rows - 1])))

}
