#include <stdio.h>

#include "visualization.h"

void explore_labyrinth(int rows, int columns, int labyrinth[][columns], int* start_row, int* start_column, int direction) {
    int new_row = *start_row;
    int new_column = *start_column;

    switch (direction){
      case 1: {
        new_column = new_column - 1;
        break;
      }

      case 2: {
        new_column = new_column + 1;
        break;
      }

      case 3: {
        new_row = new_row - 1;
        break;
      }

      case 4: {
        new_row = new_row + 1;
        break;
      }

      case 5: {
        return;
      }
    }

    if (new_row >= 0 && new_row < columns && new_column >= 0 && new_column < rows) {
        if (labyrinth[new_column][new_row] == 0) {
            labyrinth[*start_column][*start_row] = 0;
            labyrinth[new_column][new_row] = 2;

            *start_row = new_row;
            *start_column = new_column;

            visualize_labyrinth(rows, columns, labyrinth, *start_row, *start_column);
        } 
        
        else {
            printf("Cannot move into a wall!\n");
        }
    } 
      
    else {
        printf("Cannot move outside the Labyrinth\n\n");
    }
}
