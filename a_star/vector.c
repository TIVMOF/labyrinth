#include <stdlib.h>
#include <stdio.h>
#include "vector.h"
#include "graph.h"


struct vector_t* vector_init() {
	struct vector_t* new_vec = malloc(sizeof(struct vector_t));

	new_vec->size = 0;
	new_vec->values = NULL;

	return new_vec;
}

void vector_add(struct vector_t* vec, void* value) {
    vec->values = realloc(vec->values, (vec->size + 1) * sizeof(void*));
    vec->values[vec->size] = value;
    vec->size++;
}

void* vector_get(struct vector_t* vec, int index) {
    if(index > vec->size) return NULL;
    return vec->values[index];
}

//Reverses the position off all the elements of a given vector
void vector_reverse(struct vector_t* vec) {
    if(vec->size == 0) return;

    for(int i = 0; i < vec->size / 2; i++) {
        void* temp = vec->values[i];
        vec->values[i]  = vec->values[vec->size - 1 - i];
        vec->values[vec->size - 1 - i] = temp;
    }
}

void* find_node_in_vector(struct vector_t* vec, int x, int y) {
    for(int i = 0; i < vec->size; i++) {
        if(((struct graph_node_t*)vec->values[i])->x == x &&
           ((struct graph_node_t*)vec->values[i])->y == y)
            return vec->values[i];
    }

    return NULL;
}
