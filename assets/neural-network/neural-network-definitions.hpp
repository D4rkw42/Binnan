// definições de IA

#ifndef NEURAL_NETWORK_DEFINITIONS_HPP
#define NEURAL_NETWORK_DEFINITIONS_HPP

#include <vector>
#include <memory>
#include <string>

//

static const char* NN_PATH = "assets/nn/"; // localização das redes

static const double MAX_RANDOM_BIAS = 2;
static const double MAX_RANDOM_WEIGHT = 1.5;

//

class Neuron {
  public:
    std::vector<double> weights;
    double bias;

    Neuron(int _weights);
    double load(std::vector<double> values);
};

class NeuralNetwork {
  public:
    std::string type; // "NNRegular" ou "NNFuturePrice"
    std::vector<std::vector<Neuron>> layers;

    // _input_nr = número de neurônios de entrada
    // _output_nr = número de neurônios de saída
    // _hidden_layers = número de camadas ocultas
  
    NeuralNetwork(std::string type, int _input_nr, int _output_nr, int _hidden_layers);
    NeuralNetwork(void) {};
    virtual ~NeuralNetwork() {};

    virtual std::vector<double> load(std::vector<double> input);
};

//


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
