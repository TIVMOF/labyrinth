//Structure that stores the x and y coordinates
struct Cell_coords{
    int x;
    int y;
};

void generate_maze(int start_x, int start_y, int end_x, int end_y, int x, int y, int maze[][x]);