struct graph_node_t {
    struct vector_t* edges;
    int visited;
    int x;
    int y;
    int weight;
};

struct graph_edge_t {
    int weight;
    struct graph_node_t* src;
    struct graph_node_t* dest;
};
