#include <stdio.h>
#include <stdlib.h>

void labyrinth_to_file(char *file_name, int rows, int columns, int labyrinth[rows][columns]) {
  FILE *file = fopen(file_name, "w");
  if (file == NULL) {
    printf("Failed to open the file.\n");
    return;
  }

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      fprintf(file, "%d ", labyrinth[i][j]);
      printf("%d ", labyrinth[i][j]);
    }
    fprintf(file, "\n");
    printf("\n");
  }

  fclose(file);

  printf("Labyrinth successfully written to file: %s\n", file_name);
}

int **file_to_labyrinth(char *file_name, int *rows, int *columns) {
  FILE *file = fopen(file_name, "r");
  if (file == NULL) {
    printf("Failed to open the file.\n");
    return NULL;
  }

  int curr_columns = 0;
  int has_content = 0;
  
  char character;
  
  while ((character = fgetc(file)) != EOF) {
    if (character == ' '){
      continue;
    }
      
    else if (character == '\n') {
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

    } 
    
    else {
      curr_columns++;
      has_content = 1;
    }
  }

  // Reseting file pointer to the start of the file
  fseek(file, 0, SEEK_SET);

  int **labyrinth = (int **)malloc(*rows * sizeof(int *));

  for (int i = 0; i < *rows; i++) {
    labyrinth[i] = (int *)malloc(*columns * sizeof(int));

    for (int j = 0; j < *columns; j++) {
      fscanf(file, "%d", &labyrinth[i][j]);
    }
  }

  fclose(file);

  printf("Labyrinth successfully read from file: %s\n", file_name);

  return labyrinth;
}

void dynamic_to_static_matrix(int rows, int columns, int **dynamic_matrix, int static_matrix[rows][columns]) {

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      static_matrix[i][j] = dynamic_matrix[i][j];
    }
  }
}
