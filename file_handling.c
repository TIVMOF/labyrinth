#include <stdio.h>
#include <stdlib.h>

void labyrinth_to_file(char *file_name, int labyrinth[40][30], int rows,
                       int columns) {
  FILE *file = fopen(file_name, "w");
  if (file == NULL) {
    printf("Failed to open the file.\n");
    return;
  }

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      fprintf(file, "%d ", labyrinth[i][j]);
    }
    fprintf(file, "\n");
  }

  fclose(file);

  printf("Labyrinth successfully written to file: %s\n", file_name);
}

int **file_to_labyrinth(char *file_name, int *rows, int *columns, int *hero_x,
                        int *hero_y) {
  FILE *file = fopen(file_name, "r");
  if (file == NULL) {
    printf("Failed to open the file.\n");
    return NULL;
  }

  // fscanf(file, "%d", rows);
  // fscanf(file, "%d", columns);
  int curr_columns = 0;
  int has_content = 0;
  //* Calculate curr_columns and (*rows)
  char c;
  while ((c = fgetc(file)) != EOF) {
    if (c == ' ')
      continue;
    else if (c == '\n') {
      if (has_content) {
        (*rows)++;
        if ((*columns) == 0)
          (*columns) = curr_columns;
        else if (curr_columns != (*columns)) {
          fclose(file);
          printf("Incorrect file format!");
          return NULL;
        }
      }
      curr_columns = 0;
      has_content = 0;

    } else {
      curr_columns++;
      has_content = 1;
    }
  }

  //* Reset the file pointer to the beginning of the file
  fseek(file, 0, SEEK_SET);

  //* Handle the last line in the file
  if (has_content) {
    (*rows)++;
    if ((*columns) == 0)
      (*columns) = curr_columns;
    else if (curr_columns != (*columns)) {
      fclose(file);
      printf("Error! Incorrect file format.");
      return NULL;
    }
  }

  int **labyrinth = (int **)malloc(*rows * sizeof(int *));

  for (int i = 0; i < *rows; i++) {
    labyrinth[i] = (int *)malloc(*columns * sizeof(int));

    for (int j = 0; j < *columns; j++) {
      fscanf(file, "%d", &labyrinth[i][j]);

      if (labyrinth[i][j] == 2) {
        (*hero_y) = i;
        (*hero_x) = j;
      }
    }
  }

  fclose(file);

  printf("Labyrinth successfully read from file: %s\n", file_name);

  return labyrinth;
}

void dynamic_to_static_matrix(int rows, int columns, int **dynamic_matrix,
                              int static_matrix[rows][columns]) {

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      static_matrix[i][j] = dynamic_matrix[i][j];
    }
  }
}
