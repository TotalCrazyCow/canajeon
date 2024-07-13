#include "../src/grid.hpp"

int main() {

    Grid sol = {};

    for (int i=0; i != 3; ++i) {
        sol.StepAndWrite(std::string("test_out_.png") + std::to_string(i));
    };
    
    return 0;
};
