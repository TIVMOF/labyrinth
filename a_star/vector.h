struct vector_t {
	void** values;
	int size;
};

struct vector_t* vector_init();
void vector_add(struct vector_t* vec, void* value);
void* vector_get(struct vector_t* vec, int index);
void vector_reverse(struct vector_t* vec);
void* find_node_in_vector(struct vector_t* vec, int x, int y);
