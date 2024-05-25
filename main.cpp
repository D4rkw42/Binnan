#include <iostream>

#include "assets/neural-network/neural-network.hpp"
#include "core/binance/binance.hpp"

int main(int argc, char** argv) {
    auto nn = createNeuralNetwork<NN_Regular>(2, 1, 1);
    saveNeuralNetwork("teste", nn);
    auto nn2 = loadNeuralNetwork("teste");
    auto res = nn2->load(std::vector<double> {1, 2});
    std::cout << res[0];
    return 0;
}
