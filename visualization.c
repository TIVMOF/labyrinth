#include <stdio.h>

void visualize_labyrinth(int labyrinth[40][30], int rows, int columns, int hero_x, int hero_y){
    for(int i = 0; i < columns + 2; i++){
        printf("#");
    }

    printf("\n");

    for (int i = 0; i < rows; i++) {
        printf("#");

        for (int j = 0; j < columns; j++) {
            if (labyrinth[i][j] == 1) {
                printf("#");
            }

            if (labyrinth[i][j] == 0) {
                printf(" ");
            }

            if(i == hero_x && j == hero_y){
                printf("@");
            }
        }

        printf("#\n");
    }

    for(int i = 0; i < columns + 2; i++){
        printf("#");
    }

    printf("\n");
}
