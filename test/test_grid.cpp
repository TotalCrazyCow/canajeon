#include "../src/grid.hpp"

int main() {

    Grid sol = {};

    for (int i=0; i != 30; ++i) {
        sol.StepAndWrite(std::string("test_out_") + std::to_string(i) + std::string(".bmp"));
    };
    
    return 0;
};
