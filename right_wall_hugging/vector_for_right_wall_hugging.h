struct Cell{
    int x;
    int y;
};

struct _vector_t {
	struct Cell* values;
	int size;
};

struct _vector_t* _vector_init();
void _vector_add(struct _vector_t* vec, struct Cell value);
void _vector_remove_last(struct _vector_t* vec);
struct Cell _vector_get(struct _vector_t* vec, int index);
int _index_in_vector(struct _vector_t* vec, struct Cell value);
