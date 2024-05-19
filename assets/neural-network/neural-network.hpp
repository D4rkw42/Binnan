// definição das IAs do projeto

#ifndef NEURAL_NETWORK_HPP
#define NEURAL_NETWORK_HPP

#include <vector>

#include "neural-network-definitions.hpp"

//

// IA para operação básica de perído curto/longo
class NN_Regular : public NeuralNetwork {
  public:
    NN_Regular(int _input_nr, int _output_nr, int _hidden_layers) : NeuralNetwork("NNRegular", _input_nr, _output_nr, _hidden_layers) {};
    std::vector<double> load(std::vector<double> input);

};

// IA para operação de prevenção de preço
class NN_FuturePrice : public NeuralNetwork {
  public:
    NN_FuturePrice(int _input_nr, int _output_nr, int _hidden_layers) : NeuralNetwork("NNFuturePrice", _input_nr, _output_nr, _hidden_layers) {};
    std::vector<double> load(std::vector<double> input);

};

#endif
