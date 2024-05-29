#include <iostream>
#include <vector>

#include "assets/neural-network/neural-network.hpp"
#include "assets/maths.hpp"

int main(int argc, char** argv) {
    double vector[] = {10, 4, 6, 11, 20};
    GatedRecurrentUnit nn = GatedRecurrentUnit(5, 1, 2);
    
    for (int i = 0; i < 20; ++i) {
        std::cout << *(nn.load(vector)) << " ";
    }

    return 0;
}
