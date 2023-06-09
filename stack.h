typedef struct stack_node_t{
    void* data;
    struct stack_node_t* next;
    struct stack_node_t* prev;
} Stack_node;

typedef struct stack_t{
    Stack_node* head;
    Stack_node* tail;
} Stack;


Stack* stack_init();
unsigned int stack_size(Stack* q);
void stack_push(Stack* q, void* value);
void* stack_pop(Stack* q);
int stack_contains(Stack* q, void* value);
void* stack_at(Stack* q, unsigned int index);
void stack_clear(Stack* q);
void stack_destroy(Stack* q);
void stack_print(Stack* q);