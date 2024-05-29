// recursos de redes neurais

#ifndef NEURAL_NETWORK_HPP
#define NEURAL_NETWORK_HPP

#include "GatedRecurrentUnit.hpp"

template <class NeuralNetwork>
NeuralNetwork createNeuralNetwork(int input, int output, int hidden_layers);

template <class NeuralNetwork>
NeuralNetwork createBlankNeuralNeuralNetwork(void);

#endif
