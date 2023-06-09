#include <stdio.h>
#include <stdlib.h>
#include "vector.h"
#include "queue.h"
#include "../visualization.h"
#include "graph.h"


int check_down(struct graph_node_t* cell, int rows, int columns, int maze[rows][columns]) {
    if(cell->y+1 < rows && maze[cell->y+1][cell->x] == 0) {
        return 0;
    }
    return 1;
}

int check_up(struct graph_node_t* cell, int rows, int columns, int maze[rows][columns]) {
    if(cell->y-1 > 0 && maze[cell->y-1][cell->x] == 0) {
        return 0;
    }
    return 1;
}

int check_right(struct graph_node_t* cell, int rows, int columns, int maze[rows][columns]) {
    if(cell->x+1 < columns && maze[cell->y][cell->x+1] == 0) {
        return 0;
    }
    return 1;
}

int check_left(struct graph_node_t* cell, int rows, int columns, int maze[rows][columns]) {
    if(cell->x-1 > 0 && maze[cell->y][cell->x-1] == 0) {
        return 0;
    }
    return 1;
}

void connect_nodes(
    struct graph_node_t* src,
    struct graph_node_t* dest,
    double weight
) {
    struct graph_edge_t* e_for_src = (struct graph_edge_t*)malloc(sizeof(struct graph_edge_t));
    struct graph_edge_t* e_for_dest = (struct graph_edge_t*)malloc(sizeof(struct graph_edge_t));
    e_for_src->weight = weight;
    e_for_src->src = src;
    e_for_src->dest = dest;

    e_for_dest->weight = weight;
    e_for_dest->src = dest;
    e_for_dest->dest = src;

    vector_add(src->edges, e_for_src);
    vector_add(dest->edges, e_for_dest);
}

struct vector_t* generate_graph_from_file(int rows, int columns, int maze[rows][columns]) {
    //Initiating variables
    struct vector_t* nodes = vector_init();

    //Adding all the nodes from the file to a vector
    for(int i = 0; i < rows; i++) {
            for(int j = 0; j < columns; j++) {
                if(maze[i][j] != 1) {
                    struct graph_node_t* new_node = malloc(sizeof(struct graph_node_t));
                    new_node->edges = vector_init();
                    new_node->visited = 0;
                    new_node->x = j;
                    new_node->y = i;
                    new_node->weight = -1;
                    vector_add(nodes, new_node);
                }
            }

    }

    //Adding all the edges from the file to all the nodes
    //they connect
    for(int i = 0; i < nodes->size; i++) {
        int x = ((struct graph_node_t*)nodes->values[i])->x;
        int y = ((struct graph_node_t*)nodes->values[i])->y;

        if(!check_up(nodes->values[i], rows, columns, maze)) {
            connect_nodes(
                vector_get(nodes, i),
                find_node_in_vector(nodes, x, y-1),
                1
            );
        }

        if(!check_down(nodes->values[i], rows, columns, maze)) {
            connect_nodes(
                vector_get(nodes, i),
                find_node_in_vector(nodes, x, y+1),
                1
            );
        }

        if(!check_left(nodes->values[i], rows, columns, maze)) {
            connect_nodes(
                vector_get(nodes, i),
                find_node_in_vector(nodes, x-1, y),
                1
            );
        }

        if(!check_right(nodes->values[i], rows, columns, maze)) {
            connect_nodes(
                vector_get(nodes, i),
                find_node_in_vector(nodes, x+1, y),
                1
            );
        }
    }

    return nodes;
}

double heuristic_algorithm(
    struct graph_node_t* src,
    struct graph_node_t* curr,
    struct graph_edge_t* edge,
    struct graph_node_t* end
) {
    double weight = 0;
    int delta_x = abs(end->x - curr->x);
    int delta_y = abs(end->y - curr->y);


    weight = (src->weight + edge->weight + delta_x
    + delta_y);

    return weight;
}

struct vector_t* find_path(
    struct graph_node_t* start,
    struct graph_node_t* end
) {
    //Initializing variables
    start->weight = 0;
    struct queue_t* nodes = init_queue();
    queue_add(nodes, start, start->weight);
    start->visited = 1;

    //While loop, that goes through all the nodes
    while(nodes->size > 0) {
        struct graph_node_t* curr = queue_remove(nodes);
        if(curr == NULL) break;

        //If the end is reached, the if statement exits the while loop
        if(curr == end) {
            if(nodes->head != NULL) {
                if(nodes->head->priority >= curr->weight) {
                    break;
                }
            }
        }

        //For loop that goes to all the edges of a node, that haven't been visited
        for(int i = 0; i < curr->edges->size; i++) {
            struct graph_edge_t* edge = curr->edges->values[i];
            double tmp_weight = heuristic_algorithm(curr,
                             ((struct graph_edge_t*)curr->edges->values[i])->dest,
                             edge, end);
            //If a shorter path or a non-visited node is found, it's
            //priority is changed or adjusted
            if(edge->dest->weight == -1 || edge->dest->weight > tmp_weight) {
                edge->dest->weight = tmp_weight;
                if(edge->dest->visited)
                    change_node_priority(nodes, edge->dest, tmp_weight);
            }

            if(edge->dest->visited)
                continue;
            queue_add(nodes, edge->dest, edge->dest->weight);

            edge->dest->visited = 1;
        }
    }

    struct vector_t* route = vector_init();
    vector_add(route, end);
    struct graph_node_t* curr = end;

    //A reversed engineered vector for the path is created
    while(curr != start) {
        for(int i = 0; i < curr->edges->size; i++) {
          struct graph_edge_t* edge = curr->edges->values[i];
          int tmp_weight = heuristic_algorithm(
                        ((struct graph_edge_t*)curr->edges->values[i])->dest,
                        curr,
                        edge, end);
              if(tmp_weight == curr->weight) {
                curr = edge->dest;
                vector_add(route, curr);
                i = 0;
              }
        }
    }

    vector_reverse(route);

    return route;
}

void print_path(struct vector_t* route, int rows, int columns, int maze[rows][columns]) {
    for(int i = 0; i < route->size; i++) {
        visualize_labyrinth(rows, columns, maze, ((struct graph_node_t*)route->values[i])->x, ((struct graph_node_t*)route->values[i])->y);
        if(i < route->size-1)
            printf("\n\n");
    }
}

void a_star(int rows, int columns, int maze[rows][columns]) {
    struct vector_t* nodes = generate_graph_from_file(rows, columns, maze);

    struct vector_t* route =  find_path(
                        vector_get(nodes, 0),
                        vector_get(nodes, nodes->size-1)
                    );

    print_path(route, rows, columns, maze);
}
