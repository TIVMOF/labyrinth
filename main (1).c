#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "file_handling.h"
#include "generate_maze.h"
#include "labyrinth_exploration.h"
#include "visualization.h"
#include "a_star/a_star.h"
#include "right_wall_hugging/right_wall_hugging.h"

int main(void) {
  int choice = 0;
  int gen_rows = 0;
  int gen_columns = 0;
  int file_rows = 0;
  int file_columns = 0;

  int **file_labyrinth;
  int static_file_labyrinth[40][30];
  int generated_labyrinth[40][30];

  while (choice != 6) {

    printf("Choose one of the options!\n");
    printf("1. Generate a labyrinth;\n");
    printf("2. Read a labyrinth from a file;\n");
    printf("3. Write generated labyrinth in file;\n");
    printf("4. Walk around the labyrinth;\n");
    printf("5. Automatic walk around the labyrinth;\n");
    printf("6. Exit the program;\n\n");

    printf("Your choice:");
    scanf("%d", &choice);

    switch (choice) {
    case 1: {
      int seed_flag = 0;
      
      printf("Enter the size of the labyrinth!\n");

      printf("Enter the hight (3 - 40):");
      scanf("%d", &gen_rows);

      printf("Enter the width (3 - 30):");
      scanf("%d", &gen_columns);

      printf("Do you wnat to enter a seed number?\n");
      printf("1. Yes\n");
      printf("2. No\n");
      
      printf("Your choice:");
      scanf("%d", &seed_flag);

      if(seed_flag == 1){
        int seed_number = 0;
        
        printf("Enter your seed number:");
        scanf("%d", &seed_number);

        srand(seed_number);
      }

      else srand(time(NULL));

      // Check for incorrect user input hight
      while (gen_rows < 3 || gen_rows > 40) {
        printf("Incorrect hight!\n");
        printf("The hight cannot be lower than 3 or higher then 40!\n");

        printf("Enter hight (3 - 40):");
        scanf("%d", &gen_rows);
      }

      // Check for incorrect user input width
      while (gen_columns < 3 || gen_columns > 30) {
        printf("Incorrect width!\n");
        printf("The width cannot be lower than 3 or higher then 30!\n");

        printf("Enter width (3 - 30):");
        scanf("%d", &gen_columns);
      }

      generate_maze(0, 0, gen_columns - 1, gen_rows - 1, gen_columns, gen_rows,generated_labyrinth);

      visualize_labyrinth(gen_rows, gen_columns, generated_labyrinth, 0, 0);
      printf("\n");

      break;
    }

    case 2: {
      file_columns = 0;
      file_rows = 0;
      
      char file_name[50];
      
      printf("Enter the name of the file:");
      scanf("%s", file_name);

      file_labyrinth = file_to_labyrinth(file_name, &file_rows, &file_columns);

      dynamic_to_static_matrix(file_rows, file_columns, file_labyrinth,
                               static_file_labyrinth);

      visualize_labyrinth(file_rows, file_columns, static_file_labyrinth, 0, 0);

      printf("\n");

      break;
    }

    case 3: {
      char file_name[50];

      printf("Enter a name for the file:");
      scanf("%s", file_name);

      labyrinth_to_file(file_name, gen_rows, gen_columns, generated_labyrinth);

      printf("\n");

      break;
    }

    case 4: {
      int explorer_choice = 0;
      int explorer_steps = 0;

      int start_row = 0;
      int start_column = 0;

      printf("\nWhich labyrinth you want to explore?\n");
      printf("1. Generated Labyrinth;\n");
      printf("2. File Labyrinth;\n\n");

      printf("Your choice:");
      scanf("%d", &explorer_choice);

      if(explorer_choice == 1){
          if(gen_rows == 0 && gen_columns == 0){
            printf("There is no labyrinth generated!\n\n");
            break;
          }
        }

        if(explorer_choice == 2){
          if(file_rows == 0 && file_columns == 0){
            printf("There is no labyrinth read from file!\n\n");
            break;
          }
        }

      printf("\nTo make a move use:\n");
      printf("1. Up;\n");
      printf("2. Down;\n");
      printf("3. Left;\n");
      printf("4. Right;\n");
      printf("5. Exit;\n");

      if (explorer_choice == 1) {
        visualize_labyrinth(gen_rows, gen_columns, generated_labyrinth, 0, 0);
        
        while (explorer_steps != 5) {
          printf("Your choice:");
          scanf("%d", &explorer_steps);

          explore_labyrinth(gen_rows, gen_columns, generated_labyrinth, &start_row, &start_column, explorer_steps);
        }
      }

      else if (explorer_choice == 2) {
        visualize_labyrinth(file_rows, file_columns, static_file_labyrinth, 0, 0);
        
        while (explorer_steps != 5) {
          printf("Your choice:");
          scanf("%d", &explorer_steps);

          explore_labyrinth(file_rows, file_columns, static_file_labyrinth, &start_row, &start_column, explorer_steps);
        }
      }

      else printf("Incorect choice!\n\n");

      printf("\n");

      break;
    }

      case 5: {
        int algorithm_choice = 0;
        int labyrinth_choice = 0;

        printf("\nChoose which labyrinth to use:\n");
        printf("1. Generated Labyrinth\n");
        printf("2. File Labyrinth;\n\n");

        printf("Your choice:");
        scanf("%d", &labyrinth_choice);

        if(labyrinth_choice == 1){
          if(gen_rows == 0 && gen_columns == 0){
            printf("There is no labyrinth generated!\n\n");
            break;
          }
        }

        if(labyrinth_choice == 2){
          if(file_rows == 0 && file_columns == 0){
            printf("There is no labyrinth read from file!\n\n");
            break;
          }
        }
        
        printf("\nChoose which traverse algorithm to use:\n");
        printf("1. Right wall hugging;\n");
        printf("2. A Star;\n\n");

        printf("Your choice:");
        scanf("%d", &algorithm_choice);

        if(algorithm_choice == 1 && labyrinth_choice == 1){
          right_wall_hugging(gen_rows, gen_columns, generated_labyrinth);
        }

        else if(algorithm_choice == 1 && labyrinth_choice == 2){
          right_wall_hugging(file_rows, file_columns, static_file_labyrinth);
        }

        else if(algorithm_choice == 2 && labyrinth_choice == 1){
          a_star(gen_rows, gen_columns, generated_labyrinth);
        }

        else if(algorithm_choice == 2 && labyrinth_choice == 2){
          a_star(file_rows, file_columns, static_file_labyrinth);
        }

        else printf("Incorrect choice!\n\n");

        break;
      }
    }
  }
}