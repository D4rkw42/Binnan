#include "neural-network.hpp"

#include <iostream>
#include <fstream>
#include <filesystem>

#include "assets/maths.hpp"

const int BIAS_VARIATION = 10;
const int WEIGHT_VARIATION = 10;

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

//

std::shared_ptr<NeuralNetwork> NN_Regular::copy(void) {
  std::shared_ptr<NeuralNetwork> base = createBlankNeuralNetwork<NN_Regular>();
  base->layers = this->layers;
  return base;
}

std::shared_ptr<NeuralNetwork> NN_FuturePrice::copy(void) {
  std::shared_ptr<NeuralNetwork> base = createBlankNeuralNetwork<NN_FuturePrice>();
  base->layers = this->layers;
  return base;
}

//

std::shared_ptr<NeuralNetwork> loadNeuralNetwork(std::string nn_name) {
  std::ifstream file;
  std::string file_line;

  std::shared_ptr<NeuralNetwork> nn = nullptr;

  //
  
  file.open(std::string(NN_PATH) + nn_name + ".dat");
  
  //

  std::string nn_type;

  int l_id = 0;

  std::vector<Neuron> currLayer;

  while (getline(file, file_line)) {
    std::vector<std::string> data; // a informação contida em cada linha
    std::string info = "";
    
    if (l_id++ == 0) { // definição do tipo da rede neural
      if (file_line == "NNRegular") {
        nn = createBlankNeuralNetwork<NN_Regular>();
      } else if (file_line == "NNFuturePrice") {
        nn = createBlankNeuralNetwork<NN_FuturePrice>();
      }

      continue;
    }

    for (char c : file_line) {
      if (c == ' ') {
        data.push_back(info);
        info = "";

        continue;
      }

      info += c;
    }

    // atribuição de dados

    if (data[0] == "#") { // nova camada
      nn->layers.push_back(currLayer);
      currLayer.clear();
    } else { // atribuição de neurônios na mesma camada
      Neuron neuron(data.size() - 1);

      for (int i = 0; i < data.size(); ++i) {
        double value = std::stod(data[i]);

        if (i == 0) {
          neuron.bias = value;
        } else {
          neuron.weights[i - 1] = value;
        }
      }

      currLayer.push_back(neuron);
    }
  }

  //

  file.close();

  return nn;
}

void saveNeuralNetwork(std::string nn_name, std::shared_ptr<NeuralNetwork> neuralNetwork) {
  std::ofstream file;

  std::filesystem::create_directories(NN_PATH);
  file.open(std::string(NN_PATH) + nn_name + ".dat");

  file << neuralNetwork->type << "\n";
  
  for (auto layer : neuralNetwork->layers) {
    for (auto neuron : layer) {
      file << neuron.bias << " ";
      
      for (double value : neuron.weights) {
        file << value << " ";
      }

      file << "\n";
    }

    file << "# \n";
  }
  
  file.close();
}

void messNeuralNetwork(std::shared_ptr<NeuralNetwork> nn) {
  for (int layer = 0; layer < nn->layers.size(); ++layer) {
    for (int neuron = 0; neuron < nn->layers[layer].size(); ++neuron) {
      double bias_mod = random::get<double>(-BIAS_VARIATION, BIAS_VARIATION);
      nn->layers[layer][neuron].bias += bias_mod;
      
      for (int weight = 0; weight < nn->layers[layer][neuron].weights.size(); ++weight) {
        double weight_mod = random::get<double>(-WEIGHT_VARIATION, WEIGHT_VARIATION);
        nn->layers[layer][neuron].weights[weight] += weight_mod;
      }
    }
  }
}
