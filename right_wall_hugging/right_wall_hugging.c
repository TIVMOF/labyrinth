#include <stdio.h>
#include <stdlib.h>
#include "vector_for_right_wall_hugging.h"
#include "../visualization.h"


int _check_right(int rows, int columns, int maze[rows][columns], struct Cell cord) {
    if(cord.x-1 < 0 || maze[cord.y][cord.x-1] != 0) {
        if(maze[cord.y][cord.x-1] != 3)
            return 0;
    }

    return 1;
}

int _check_front(int rows, int columns, int maze[rows][columns], struct Cell cord) {
    if(cord.y+1 >= rows || maze[cord.y+1][cord.x] != 0) {
        if(maze[cord.y+1][cord.x] != 3)
            return 0;
    }

    return 1;
}

int _check_left(int rows, int columns, int maze[rows][columns], struct Cell cord) {
    if(cord.x+1 >= columns || maze[cord.y][cord.x+1] != 0) {
        if(maze[cord.y][cord.x+1] != 3)
            return 0;
    }

    return 1;
}

int _check_back(int rows, int columns, int maze[rows][columns], struct Cell cord) {
    if(cord.y-1 < 0 || maze[cord.y-1][cord.x] != 0) {
        if(maze[cord.y-1][cord.x] != 3)
            return 0;
    }


    return 1;
}

char calculate_direction(struct Cell curr, struct _vector_t* all_past_moves) {
    if(all_past_moves->size <= 1) return 'f';
    struct Cell past_move;
    past_move = _vector_get(all_past_moves, all_past_moves->size-2);

    if(past_move.y+1 == curr.y)
        return 'f';

    if(past_move.y-1 == curr.y)
        return 'b';

    if(past_move.x+1 == curr.x)
        return 'l';

    if(past_move.x-1 == curr.x)
        return 'r';

    return 'f';
}

struct Cell _check_next(int rows, int columns, int maze[rows][columns], struct Cell curr,
                       struct _vector_t* all_past_moves) {

    char direction = calculate_direction(curr, all_past_moves);
    char seq[4];
    int dead_end = 1;

    switch(direction) {
    case 'f':
        seq[0] = 'r';
        seq[1] = 'f';
        seq[2] = 'l';
        seq[3] = 'b';
        break;

    case 'r':
        seq[0] = 'b';
        seq[1] = 'r';
        seq[2] = 'f';
        seq[3] = 'l';
        break;

    case 'l':
        seq[0] = 'f';
        seq[1] = 'l';
        seq[2] = 'b';
        seq[3] = 'r';
        break;

    case 'b':
        seq[0] = 'l';
        seq[1] = 'b';
        seq[2] = 'r';
        seq[3] = 'f';
        break;

    default:
        printf("Invalid direction!\n");
        break;
    }

    for(int i = 0; i < 4 && dead_end; i++) {
        switch(seq[i]) {
        case 'r' :
            if(_check_right(rows, columns, maze, curr)) {
                curr.x -= 1;
                dead_end = 0;
            }
            break;

        case 'l' :
            if(_check_left(rows, columns, maze, curr)) {
                curr.x += 1;
                dead_end = 0;
            }
            break;

        case 'f' :
            if(_check_front(rows, columns, maze, curr)) {
                curr.y += 1;
                dead_end = 0;
            }
            break;

        case 'b' :
            if(_check_back(rows, columns, maze, curr)) {
                curr.y -= 1;
                dead_end = 0;
            }
            break;
        }
    }

    return curr;
}

int _check_same_as_last(struct _vector_t* all_past_moves, struct Cell curr) {
    if(curr.x == all_past_moves->values[all_past_moves->size-1].x &&
       curr.y == all_past_moves->values[all_past_moves->size-1].y)
        return 1;

    return 0;
}

void right_wall_hugging(int rows, int columns, int maze[rows][columns]) {
    struct _vector_t* all_past_moves = _vector_init();
    struct Cell cord;
    cord.x = 0;
    cord.y = 0;

    _vector_add(all_past_moves, cord);
    while(cord.x != columns-1 || cord.y != rows-1) {
        maze[cord.y][cord.x] = 4;
        cord = _check_next(rows, columns, maze, cord, all_past_moves);

        if(!_check_same_as_last(all_past_moves, cord)) {
            _vector_add(all_past_moves, cord);
        }
        else {
            cord = all_past_moves->values[_index_in_vector(all_past_moves, cord)-1];
            _vector_add(all_past_moves, cord);
        }
    }

    for(int i = 0; i < all_past_moves->size; i++) {
        visualize_labyrinth(rows, columns, maze, all_past_moves->values[i].x, all_past_moves->values[i].y);
        printf("\n\n");
    }
}
