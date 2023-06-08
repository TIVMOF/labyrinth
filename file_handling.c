#include <stdio.h>

void labyrinth_to_file(char* file_name, int labyrinth[40][30], int rows, int columns) {
    FILE* file = fopen(file_name, "w");
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
