#include <stdio.h>

void explore_labyrinth(int rows, int columns, int labyrinth[][cols], int* start_row, int* start_column, int direction) {
    int new_row = *start_row;
    int new_column = *start_column;

    if (direction == 1 && *start_row > 0) {  // Up
        new_row = *start_row - 1;
    } 
    
    else if (direction == 2 && *start_row < rows - 1) {  // Down
        new_row = *start_row + 1;
    } 
    
    else if (direction == 3 && *start_column > 0) {  // Left
        new_column = *start_column - 1;
    } 
    
    else if (direction == 4 && *start_column < columns - 1) {  // Right
        new_column = *start_column + 1;
    }

    if (new_row >= 0 && new_row < rows && new_column >= 0 && new_column < columns) {
        if (labyrinth[new_row][new_column] == 0) {
            labyrinth[*start_row][*start_column] = 0;
            labyrinth[new_row][new_column] = 2;

            *start_row = new_row;
            *start_column = new_column;
        } 
        
        else {
            printf("Cannot move into a wall!\n");
        }
    } 
      
    else {
        printf("Cannot move outside the matrix!\n");
    }
}