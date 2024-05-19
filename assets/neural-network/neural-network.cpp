#include "neural-network.hpp"

#include "assets/maths.hpp"

//

std::vector<double> NN_Regular::load(std::vector<double> input) {
  std::vector<double> output = input;

  for (int layer = 0; layer < layers.size(); ++layer) {
    std::vector<double> layerOutput;
    
    for (int neuron = 0; neuron < layers[layer].size(); ++neuron) {
      std::vector<double> layerInput = (layer == 0)? std::vector<double> {output[neuron]} : output;
      double out = layers[layer][neuron].load(layerInput);
      
      layerOutput.push_back(out);
    }

    if (layer == 0 || layer == layers.size() - 1) {
      sigmoid(layerOutput);
    } else {
      LeakyReLu(layerOutput);
    }

    output = layerOutput;
    layerOutput.clear();
  }

  for (double& value : output) {
    value = (value > 0.5f)? 1 : 0;
  }
  
  return output;
}

std::vector<double> NN_FuturePrice::load(std::vector<double> input) {
  std::vector<double> output = input;

  for (int layer = 0; layer < layers.size(); ++layer) {
    std::vector<double> layerOutput;

    for (int neuron = 0; neuron < layers[layer].size(); ++neuron) {
      std::vector<double> layerInput = (layer == 0)? std::vector<double> {output[neuron]} : output;
      double out = layers[layer][neuron].load(layerInput);

      layerOutput.push_back(out);
    }

    if (layer == 0 || layer == layers.size() - 1) {
      sigmoid(layerOutput);
    } else if (layer == layers.size() - 1) {
      ReLu(layerOutput);
    } else {
      LeakyReLu(layerOutput);
    }

    output = layerOutput;
    layerOutput.clear();
  }

  return output;
}
