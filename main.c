#include <stdio.h>
#include <stdlib.h>

#include "visualization.h"

int main(void) {
  int choice = 0;

   int maze[40][30] = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1},
        {1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 1},
        {1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1},
        {1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 1},
        {1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1},
        {1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1}
   };

  while(choice != 6){
    printf("Choose one of the options!\n");
    printf("1. Generate a labyrinth;\n");
    printf("2. Read a labyrinth from a file;\n");
    printf("3. Write a labyrinth in file;\n");
    printf("4. Walk around the labyrinth;\n");
    printf("5. Automatic walk around the labyrinth;\n");
    printf("6. Exit the program;\n\n");

    printf("Your choice:");
    scanf("%d", &choice);

    switch(choice){
      case 1:{
        int width = 0;
        int hight = 0;

        printf("Enter the size of the labyrinth!\n");
        
        printf("Enter the hight (3 - 40):");
        scanf("%d", &hight);

        printf("Enter the width (3 - 30):");
        scanf("%d", &width);

        // Check for incorrect user input hight
        while(hight < 3 || hight > 40){
          printf("Incorrect hight!\n");
          printf("The hight cannot be lower than 3 or higher then 40!\n");
          
          printf("Enter hight (3 - 40):");
          scanf("%d", &hight);
        }

        // Check for incorrect user input width
        while(width < 3 || width > 30){
          printf("Incorrect width!\n");
          printf("The width cannot be lower than 3 or higher then 30!\n");
          
          printf("Enter width (3 - 30):");
          scanf("%d", &width);
        }

        visualize_labyrinth(maze, 40, 30);

        break;
      }
    }
  }
}