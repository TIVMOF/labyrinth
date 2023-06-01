#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <"stack.h">
//1 - wall
//0 - empty

struct Cell{
    int x;
    int y;
};

void generate_maze(int star, int end_x, int end_y, int x, int y){
    struct Cell curr;
    
    start_again(x, y, arr, &curr, start_x, start_y, end_x, end_y);

    int rand_direction;
    struct stack_t past_cells = stack_init();
    do{
        maze[curr.y][curr.x] = 0;
        stack_push(past_cells, curr);

        if((is_visitable(x, y, maze, curr.x, cuur.y-1, stack_at(past_cells, stack_size(past_cells)-1))) ||
        (is_visitable(x, y, maze, curr.x-1, cuur.y, stack_at(past_cells, stack_size(past_cells)-1))) ||
        (is_visitable(x, y, maze, curr.x, cuur.y+1, stack_at(past_cells, stack_size(past_cells)-1))) ||
        (is_visitable(x, y, maze, curr.x+1, cuur.y, stack_at(past_cells, stack_size(past_cells)-1)))){
            struct Cell possible_cell;
            do{
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
            }while(is_visitable(x, y, maze, possible_cell.x, possible_cell.y, stack_at(past_cells, stack_size(past_cells)-1)));
            curr.x = possible_cell.x;
            curr.y = possible_cell.y;



        }else{
            curr.x = stack_at(past_cells, stack_size(past_cells)-1).x;
            curr.y = stack_at(past_cells, stack_size(past_cells)-1).y;
            stack_pop(past_cells);
        }

        if(stack_size(past_cells) == 0 &&
        !is_visitable(x, y, maze, curr.x, curr.y-1, curr)
        !is_visitable(x, y, maze, curr.x-1, curr.y, curr)
        !is_visitable(x, y, maze, curr.x, curr.y+1, curr)
        !is_visitable(x, y, maze, curr.x+1, curr.y, curr)){
            start_again(x, y, arr, &curr, start_x, start_y, end_x, end_y);
        }

    }while(curr.x != end.x && curr.y != end.y);
}

int is_visitable(int x, int y, int maze[][x], int curr_x, int curr_y, struct Cell last_cell){
    if(curr_x < 0 || curr_x >= x ||
    curr_y < 0 || curr_y >= y
    ){
        return 0;
    }

    if(maze[curr_y][curr_x] == 0){
        return 0;
    }

    if((maze[curr_y][curr_x-1] == 1 && curr_y != last_cell.y && curr_x-1 != last_cell.x) ||
    (maze[curr_y+1][curr_x] == 1 && curr_y+1 != last_cell.y && curr_x != last_cell.x) ||
    (maze[curr_y][curr_x+1] == 1 && curr_y != last_cell.y && curr_x+1 != last_cell.x) ||
    (maze[curr_y-1][curr_x] == 1 && curr_y-1 != last_cell.y && curr_x != last_cell.x)
    ){
        return 0;
    }

    return 1;
}

void start_again(int x, int y, int (*arr)[x], struct Cell* curr, int start_x, int start_y, int end_x, int end_y){
    for(int i = 0 ; i  < y ; i++){
        for(int j = 0 ; j  < x ; j++){
            maze[i][j] = -1;
        }
    }

    (*curr).x = start_x;
    (*curr).y = start_y;

    maze[start_x][start_y] = 2;
    maze[end_x][end_y] = 3;
}

int main () {

    return 0;
}