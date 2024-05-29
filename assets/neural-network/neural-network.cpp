// recursos de redes neurais

#include "neural-network.hpp"

template <class NeuralNetwork>
NeuralNetwork createNeuralNetwork(int input, int output, int hidden_layers) {
    return NeuralNetwork(input, output, hidden_layers);
}

template <class NeuralNetwork>
NeuralNetwork createBlankNeuralNeuralNetwork(void) {
    return NeuralNetwork();
}
