#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "stack.h"

//0 - empty
//1 - wall
//2 - start
//3 - end

//Structure that stores the x and y coordinates
struct Cell{
    int x;
    int y;
};

void print(int x, int y, int maze[][x]){
    for(int i = 0 ; i  < y ; i++){
        for(int j = 0 ; j  < x ; j++){
            printf("%d ", maze[i][j]);
        }
        printf("\n");
    }
}

// removes the 0s and 1s
void start_again(int x, int y, int maze[][x], struct Cell* curr, int start_x, int start_y, int end_x, int end_y){
    for(int i = 0 ; i  < y ; i++){
        for(int j = 0 ; j  < x ; j++){
            maze[i][j] = -1;
        }
    }

    (*curr).x = start_x;
    (*curr).y = start_y;

    maze[start_y][start_x] = 2;
    maze[end_y][end_x] = 3;
}

//Check if a cell can be set as 0
int is_visitable(int x, int y, int maze[][x], int curr_x, int curr_y, struct Cell last_cell){
    if(curr_x < 0 || curr_x >= x ||
    curr_y < 0 || curr_y >= y
    ){
        return 0;
    }

    if(maze[curr_y][curr_x] == 0){
        return 0;
    }

    if((maze[curr_y][curr_x-1] == 0 && curr_y != last_cell.y && curr_x-1 != last_cell.x) ||
    (maze[curr_y+1][curr_x] == 0 && curr_y+1 != last_cell.y && curr_x != last_cell.x) ||
    (maze[curr_y][curr_x+1] == 0 && curr_y != last_cell.y && curr_x+1 != last_cell.x) ||
    (maze[curr_y-1][curr_x] == 0 && curr_y-1 != last_cell.y && curr_x != last_cell.x)
    ){
        return 0;
    }
    return 1;
}

//sets all the -1s to 1s
void set_walls(int start_x, int start_y, int end_x, int end_y, int x, int y, int maze[][x]){
    for(int i = 0 ; i  < y ; i++){
        for(int j = 0 ; j  < x ; j++){
            if(maze[i][j] == -1){
                maze[i][j] = 1;
            }
        }
    }

    maze[start_y][start_x] = 2;
    maze[end_y][end_x] = 3;
}

//Generates a random maze by start and end coordinates
void generate_maze(int start_x, int start_y, int end_x, int end_y, int x, int y, int maze[][x]){
    struct Cell curr;
    
    //Sets all the cells -1(except the start and the end)
    start_again(x, y, maze, &curr, start_x, start_y, end_x, end_y);

    int rand_direction;
    struct stack_t* winning_path = stack_init();
    struct Cell curr_copies[x*y];
    size_t curr_copies_index = 0;

    //do while that generates a random path from 2 to 3
    do{
        if(maze[curr.y][curr.x] != 0){ //sets the current cell to 0
            maze[curr.y][curr.x] = 0;
            curr_copies[curr_copies_index].x = curr.x;
            curr_copies[curr_copies_index].y = curr.y;
            stack_push(winning_path, &curr_copies[curr_copies_index]);
            curr_copies_index++;
        }

        //checks if any of the neighboring cells can be 0 
        if(is_visitable(x, y, maze, curr.x, curr.y-1, curr) ||
        is_visitable(x, y, maze, curr.x-1, curr.y, curr) ||
        is_visitable(x, y, maze, curr.x, curr.y+1, curr) ||
        is_visitable(x, y, maze, curr.x+1, curr.y, curr)){
            struct Cell possible_cell;
            do{ //picks a random neighboring cell
                rand_direction = rand()%4;
                switch(rand_direction){
                    case 0:
                        possible_cell.x = curr.x;
                        possible_cell.y = curr.y-1;
                        break;
                    case 1:
                        possible_cell.x = curr.x-1;
                        possible_cell.y = curr.y;
                        break;
                    case 2:
                        possible_cell.x = curr.x;
                        possible_cell.y = curr.y+1;
                        break;
                    case 3:
                        possible_cell.x = curr.x+1;
                        possible_cell.y = curr.y;
                        break;
            }
            }while(!is_visitable(x, y, maze, possible_cell.x, possible_cell.y, curr));
            curr.x = possible_cell.x;
            curr.y = possible_cell.y;

        }else{
            //No cell can be set as 0. So goes back to the last visited cell
            curr.x = (*(struct Cell*)stack_at(winning_path, 0)).x;
            curr.y = (*(struct Cell*)stack_at(winning_path, 0)).y;
            stack_pop(winning_path);
        }

        if(stack_size(winning_path) == 0 && // If the path does not rech the end, it starts over
        !is_visitable(x, y, maze, curr.x, curr.y-1, curr) &&
        !is_visitable(x, y, maze, curr.x-1, curr.y, curr) &&
        !is_visitable(x, y, maze, curr.x, curr.y+1, curr) &&
        !is_visitable(x, y, maze, curr.x+1, curr.y, curr)){
            start_again(x, y, maze, &curr, start_x, start_y, end_x, end_y);
        }

    }while(curr.x != end_x || curr.y != end_y);


    maze[end_y][end_x] = 0; // sets the end to 0 so that there is only one correct path
    struct Cell past_cells_copies[x*y];
    size_t past_cells_copies_index = 0;
    for(int i =  stack_size(winning_path)-1 ; i >= 0 ; i--){ //creates all the paths that does not reach the end
        
        curr.x = (*(struct Cell*)stack_at(winning_path, i)).x;
        curr.y = (*(struct Cell*)stack_at(winning_path, i)).y;
        struct stack_t* past_cells = stack_init();

        //while there is a neighboring cell that can be set as 0
        while((is_visitable(x, y, maze, curr.x, curr.y-1, curr)) || 
        (is_visitable(x, y, maze, curr.x-1, curr.y, curr)) ||
        (is_visitable(x, y, maze, curr.x, curr.y+1, curr)) ||
        (is_visitable(x, y, maze, curr.x+1, curr.y, curr)) ||
        stack_size(past_cells) > 1){

            if((is_visitable(x, y, maze, curr.x, curr.y-1, curr)) ||
                (is_visitable(x, y, maze, curr.x-1, curr.y, curr)) ||
                (is_visitable(x, y, maze, curr.x, curr.y+1, curr)) ||
                (is_visitable(x, y, maze, curr.x+1, curr.y, curr))){
                    struct Cell possible_cell;
                    do{ // picks a random neighboring cell that can be set as 0
                        rand_direction = rand()%4;
                        switch(rand_direction){
                            case 0:
                                possible_cell.x = curr.x;
                                possible_cell.y = curr.y-1;
                                break;
                            case 1:
                                possible_cell.x = curr.x-1;
                                possible_cell.y = curr.y;
                                break;
                            case 2:
                                possible_cell.x = curr.x;
                                possible_cell.y = curr.y+1;
                                break;
                            case 3:
                                possible_cell.x = curr.x+1;
                                possible_cell.y = curr.y;
                                break;
                    }
                    }while(!is_visitable(x, y, maze, possible_cell.x, possible_cell.y, curr));
                    
                    past_cells_copies[past_cells_copies_index].x = curr.x;
                    past_cells_copies[past_cells_copies_index].y = curr.y;
                    
                    past_cells_copies_index++;
                    maze[curr.y][curr.x] = 0;
                    curr.x = possible_cell.x;
                    curr.y = possible_cell.y;
                    stack_push(past_cells, &past_cells_copies[past_cells_copies_index]);
            }else{ // goes back to the last cell in the stack
                curr.x = (*(struct Cell*)stack_at(past_cells, 0)).x;
                curr.y = (*(struct Cell*)stack_at(past_cells, 0)).y;
                stack_pop(past_cells);
            }
        }
        stack_destroy(past_cells);
    }
    stack_destroy(winning_path);

    // sets the walls
    set_walls(start_x, start_y, end_x, end_y, x, y, maze);
}

int main () {
    int maze[8][8];
    generate_maze(0, 0, 7, 7, 8, 8, maze);
    print(8, 8, maze);
    return 0;
}