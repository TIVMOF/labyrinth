void labyrinth_to_file(char *file_name, int rows, int columns, int labyrinth[rows][columns]);

int **file_to_labyrinth(char *file_name, int *rows, int *columns);

void dynamic_to_static_matrix(int rows, int columns, int **dynamic_matrix, int static_matrix[][columns]);
