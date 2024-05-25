#include "neural-network-definitions.hpp"

#include <iostream>

#include "assets/maths.hpp" // maths.hpp
#include "assets/utils.hpp"

const char* NN_PATH = "assets/nn/"; // localização das redes

const double MAX_RANDOM_BIAS = 2;
const double MAX_RANDOM_WEIGHT = 1.5;

//

Neuron::Neuron(int _weights) {
  bias = random::get<double>(-MAX_RANDOM_BIAS, MAX_RANDOM_BIAS);

  for (int w = 0; w < _weights; ++w) {
    weights.push_back(random::get<double>(-MAX_RANDOM_WEIGHT, MAX_RANDOM_WEIGHT));
  }
}

double Neuron::load(std::vector<double> values) {
  double output = 0;
  
  for (int i = 0; i < weights.size(); ++i) {
    output += values[i] * weights[i];
  }

  return output + bias;
}

//

NeuralNetwork::NeuralNetwork(std::string _type) {
  type = _type;
}

NeuralNetwork::NeuralNetwork(std::string _type, int _input_nr, int _output_nr, int _hidden_layers) {
  type = _type;

  //
  
  int hiddenLayer_nr_amount = (_input_nr + _output_nr) / 2;
  int nr_perLayer = hiddenLayer_nr_amount / _hidden_layers;

  nr_perLayer = (nr_perLayer > 0)? nr_perLayer : 1;

  for (int layer = 0; layer < _hidden_layers + 2; ++layer) {
    std::vector<Neuron> newLayer;

    int nr_amount = nr_perLayer;
    
    if (layer == 0) {
      nr_amount = _input_nr;
    } else if (layer == _hidden_layers + 1) {
      nr_amount = _output_nr;
    }

    for (int neuron = 0; neuron < nr_amount; ++neuron) {
      int weight_amount = nr_perLayer;

      if (layer == 0) {
        weight_amount = 1;
      } else if (layer == 1) {
        weight_amount = _input_nr;
      }
      
      newLayer.push_back(Neuron(weight_amount));
    }

    layers.push_back(newLayer);
    
  }
}

std::vector<double> NeuralNetwork::load(std::vector<double> input) {
  return std::vector<double> {0};
}

std::shared_ptr<NeuralNetwork> NeuralNetwork::copy(void) {
  return std::shared_ptr<NeuralNetwork>(this);
}
