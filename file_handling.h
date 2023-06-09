void labyrinth_to_file(char *file_name, int labyrinth[40][30], int rows,
                       int columns);

int **file_to_labyrinth(char *file_name, int *rows, int *columns, int * hero_x, int * hero_y);

void dynamic_to_static_matrix(int rows, int columns, int **dynamic_matrix,
                              int static_matrix[][columns]);