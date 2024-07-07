#include <vector>

const int DIMENSION = 2;
const int GRID_SIZE = 101;

struct Grid {
    double x[GRID_SIZE];
    double y[GRID_SIZE];
};

Grid drawGrid() {

    Grid domain;
    double x_min = 0;
    double x_max = 1;
    double y_min = 0;
    double y_max = 1;

    double step = (x_max - x_min)/(GRID_SIZE-1);

    for (int i = 0; i < GRID_SIZE; i++) {
        domain.x[i] = x_min + i*step;
        domain.y[i] = y_min + i*step;
    }

    return domain;
}