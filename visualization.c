#include <stdio.h>

void visualize_labyrinth(int rows, int columns, int labyrinth[rows][columns],
                         int hero_x, int hero_y) {
  for (int i = 0; i < columns + 2; i++) {
    printf("_");
  }

  printf("\n");
  for (int i = 0; i < rows; i++) {
    printf("|");

    for (int j = 0; j < columns; j++) {
      if (i == hero_x && j == hero_y) {
        printf("@");
      }

      else if (labyrinth[i][j] == 1) {
        printf("#");
      }

      else
        printf(" ");
    }

    printf("|\n");
  }

  for (int i = 0; i < columns + 2; i++) {
    printf("T");
  }

  printf("\n");
}
