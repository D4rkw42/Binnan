#include "neural-network.hpp"

#include <iostream>
#include <fstream>
#include <filesystem>

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

//

std::shared_ptr<NeuralNetwork> loadNeuralNetwork(std::string nn_name) {
  std::ifstream file;
  std::string file_line;

  std::shared_ptr<NeuralNetwork> nn = nullptr;

  //
  
  file.open(std::string(NN_PATH) + nn_name + ".dat");
  
  //

  std::string nn_type;
  file >> nn_type;

  if (nn_type == "NNRegular") {
    nn = createBlankNeuralNetwork<NN_Regular>();
  } else if (nn_type == "NNFuturePrice") {
    nn = createBlankNeuralNetwork<NN_FuturePrice>();
  }

  while (getline(file, file_line)) {
    std::vector<std::string> data; // a informação contida em cada linha
    std::string info;
    
    for (char c : file_line) {
      if (to_string(c) == " ") {
        data.push_back(info);
        info = "";

        continue;
      }

      info+= to_string(c);
    }

    // adicionar as informações na rede neural
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

      file << "/\n";
    }

    file << "#\n";
  }
  
  file.close();
}
