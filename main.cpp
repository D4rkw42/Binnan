#include <iostream>

#include "assets/neural-network/neural-network.hpp"

int main(int argc, char** argv) {
    auto nn = loadNeuralNetwork("nn1");
    std::cout << nn->type << "\n";

    return 0;
}
