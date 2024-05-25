#include <iostream>
#include <vector>

#include "assets/neural-network/neural-network.hpp"
#include "core/binance/binance.hpp"

int main(int argc, char** argv) {
    auto nn1 = createNeuralNetwork<NN_Regular>(2, 1, 2);
    auto nn2 = nn1->copy();
    messNeuralNetwork(nn2);
    std::cout << (nn1->load(std::vector<double> {2, 4})[0]) << "\n";
    std::cout << (nn2->load(std::vector<double> {2, 4})[0]);

    return 0;
}
