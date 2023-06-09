#include <stdlib.h>
#include <stdio.h>
#include "vector_for_right_wall_hugging.h"

struct _vector_t* _vector_init() {
	struct _vector_t* new_vec = malloc(sizeof(struct _vector_t));

	new_vec->size = 0;
	new_vec->values = NULL;

	return new_vec;
}

void _vector_add(struct _vector_t* vec, struct Cell value) {
    vec->values = realloc(vec->values, (vec->size + 1) * sizeof(struct Cell));
    vec->values[vec->size] = value;
    vec->size++;
}

void _vector_remove_last(struct _vector_t* vec) {
    vec->values = realloc(vec->values, (vec->size - 1) * sizeof(struct Cell));
    vec->size--;
}

struct Cell _vector_get(struct _vector_t* vec, int index) {
  if(index >= vec->size) return vec->values[0];
  return vec->values[index];
}

void _vector_print(struct _vector_t* vec) {
    for(int i = 0; i < vec->size; i++) {
        printf("\n%d.%d %d", i, vec->values[i].x, vec->values[i].y);
    }
}

int _index_in_vector(struct _vector_t* vec, struct Cell value) {
    for(int i = 0; i < vec->size; i++) {
        if(vec->values[i].x == value.x &&
           vec->values[i].y == value.y)
            return i;
    }

    return -1;
}
