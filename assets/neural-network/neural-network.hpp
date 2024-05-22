// definição das IAs do projeto

#ifndef NEURAL_NETWORK_HPP
#define NEURAL_NETWORK_HPP

#include <vector>
#include <string>

#include "neural-network-definitions.hpp"

//

// IA para operação básica de perído curto/longo
class NN_Regular : public NeuralNetwork {
  public:
    NN_Regular(int _input_nr, int _output_nr, int _hidden_layers) : NeuralNetwork("NNRegular", _input_nr, _output_nr, _hidden_layers) {};
    NN_Regular(void): NeuralNetwork("NNRegular") {}; // for empty nn

    std::vector<double> load(std::vector<double> input);

};

// IA para operação de prevenção de preço
class NN_FuturePrice : public NeuralNetwork {
  public:
    NN_FuturePrice(int _input_nr, int _output_nr, int _hidden_layers) : NeuralNetwork("NNFuturePrice", _input_nr, _output_nr, _hidden_layers) {};
    NN_FuturePrice(void): NeuralNetwork("NNFuturePrice") {};
    
    std::vector<double> load(std::vector<double> input);

};

// definição de crição e modificação

template <class NNType>
std::shared_ptr<NeuralNetwork> createNeuralNetwork(int _input_nr, int _output_nr, int _hidden_layers) {
  std::shared_ptr<NNType> nn = std::make_shared<NNType>(_input_nr, _output_nr, _hidden_layers);
  return std::dynamic_pointer_cast<NeuralNetwork>(nn);
}

template <class NNType>
std::shared_ptr<NeuralNetwork> createBlankNeuralNetwork(void) {
  std::shared_ptr<NNType> nn = std::make_shared<NNType>();
  return std::dynamic_pointer_cast<NeuralNetwork>(nn);
}

std::shared_ptr<NeuralNetwork> loadNeuralNetwork(std::string nn_name);

void saveNeuralNetwork(std::string nn_name, std::shared_ptr<NeuralNetwork> neuralNetwork);

#endif
