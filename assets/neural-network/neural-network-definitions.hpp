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
  
    NeuralNetwork(std::string _type, int _input_nr, int _output_nr, int _hidden_layers);
    NeuralNetwork(std::string _type);

    virtual ~NeuralNetwork() {};

    virtual std::vector<double> load(std::vector<double> input);

};

#endif
