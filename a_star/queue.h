struct queue_node_t {
    struct queue_node_t* next;
    void* value;
    int name;
    int priority;
};

struct queue_t {
    struct queue_node_t* head;;
    int size;
};

struct queue_t* init_queue();
void queue_add(struct queue_t* q, void* value, int priority);
void* queue_remove(struct queue_t* q);
int change_node_priority (struct queue_t* q, void* node, int new_priority);
