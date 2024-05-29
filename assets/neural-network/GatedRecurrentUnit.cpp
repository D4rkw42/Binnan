// Rede Gathed Recurrent Unit (GRU)

#include "GatedRecurrentUnit.hpp"

#include <cstdlib>

#include "assets/maths.hpp"

const int MAX_RANDOM_WEIGHT = 30;
const int MAX_RANDOM_BIAS = 30;

// GRU Hidden Neuron

GRU_HiddenLayerNeuron::GRU_HiddenLayerNeuron(int input) {
    this->Wh = new double[input];
    this->Wr = new double[input];
    this->Wz = new double[input];

    this->weights = new double[input];

    for (int i = 0; i < input; ++i) {
        this->Wh[i] = random::get<double>(-MAX_RANDOM_WEIGHT, MAX_RANDOM_WEIGHT);
        this->Wr[i] = random::get<double>(-MAX_RANDOM_WEIGHT, MAX_RANDOM_WEIGHT);
        this->Wz[i] = random::get<double>(-MAX_RANDOM_WEIGHT, MAX_RANDOM_WEIGHT);

        this->weights[i] = random::get<double>(-MAX_RANDOM_WEIGHT, MAX_RANDOM_WEIGHT);
    }

    this->Uh = random::get<double>(-MAX_RANDOM_WEIGHT, MAX_RANDOM_WEIGHT);
    this->Ur = random::get<double>(-MAX_RANDOM_WEIGHT, MAX_RANDOM_WEIGHT);
    this->Uz = random::get<double>(-MAX_RANDOM_WEIGHT, MAX_RANDOM_WEIGHT);

    this->Bh = random::get<double>(-MAX_RANDOM_BIAS, MAX_RANDOM_BIAS);
    this->Br = random::get<double>(-MAX_RANDOM_BIAS, MAX_RANDOM_BIAS);
    this->Bz = random::get<double>(-MAX_RANDOM_BIAS, MAX_RANDOM_BIAS);

    this->bias = random::get<double>(-MAX_RANDOM_BIAS, MAX_RANDOM_BIAS);

    this->ht_1 = 0;
    this->inputSize = input;
}

GRU_HiddenLayerNeuron::~GRU_HiddenLayerNeuron() {
    delete[] this->Wh;
    delete[] this->Wr;
    delete[] this->Wz;
    delete[] this->weights;
}


double* GRU_HiddenLayerNeuron::calculateGate(double* input, double* weights, double uWeight, double bias) {
    double* output = new double[this->inputSize];

    for (int i = 0; i < this->inputSize; ++i) {
        output[i] = sigmoid(input[i] * weights[i] + this->ht_1 * uWeight + bias);
    }

    return output;
}

double* GRU_HiddenLayerNeuron::candidateGate(double* input) {
    double* output = new double[this->inputSize];
    double* rt = calculateGate(input, this->Wr, this->Ur, this->Br);

    for (int i = 0; i < this->inputSize; ++i) {
        output[i] = tanh(this->Wh[i] * input[i] + this->Uh * (rt[i] * this->ht_1) + this->Bh);
    }

    delete[] rt;
    return output;
}


double GRU_HiddenLayerNeuron::load(double* input) {
    double* zt = calculateGate(input, this->Wz, this->Uz, this->Bz);
    double* candidates = candidateGate(input);

    double output = 0;


    for (int i = 0; i < this->inputSize; ++i) {
        output += this->weights[i] * ((1 - zt[i]) * this->ht_1 + zt[i] * candidates[i]) + this->bias;
    }

    output = ReLu(output + bias);
    this->ht_1 = output;

    delete[] zt;
    delete[] candidates;
    return output;
}

// GRU Basic Neuron

GRU_BasicNeuron::GRU_BasicNeuron(int input) {
    this->inputSize = input;
    this->weights = new double[input];

    for (int i = 0; i < input; ++i) {
        this->weights[i] = random::get<double>(-MAX_RANDOM_WEIGHT, MAX_RANDOM_WEIGHT);
    }

    this->bias = random::get<double>(-MAX_RANDOM_BIAS, MAX_RANDOM_BIAS);
}

GRU_BasicNeuron::~GRU_BasicNeuron() {
    delete[] this->weights;
}

double GRU_BasicNeuron::load(double* input) {
    double output = 0;

    for (int i = 0; i < this->inputSize; ++i) {
        output += input[i] * this->weights[i];
    }

    return sigmoid(output + bias);
}

// neural network

GatedRecurrentUnit::GatedRecurrentUnit(int input, int output, int hidden_layers) {
    this->inputSize = input;
    this->outputSize = output;
    this->hiddenLayerSize = hidden_layers;

    this->ES_Layers = new GRU_BasicNeuron**[2];
    this->hiddenLayers = new GRU_HiddenLayerNeuron**[hidden_layers];

    // hidden layers

    int lastLayerSize = input;

    for (int i = 0; i < hidden_layers; ++i) {
        int numOfNeurons = (lastLayerSize + output) / 2;

        this->hiddenLayers[i] = (GRU_HiddenLayerNeuron**)malloc(sizeof(GRU_HiddenLayerNeuron**) * numOfNeurons);

        for (int n = 0; n < numOfNeurons; ++n) {
            this->hiddenLayers[i][n] = new GRU_HiddenLayerNeuron(lastLayerSize);
        }

        lastLayerSize = numOfNeurons;
    }

    // es layer

    this->ES_Layers[0] = (GRU_BasicNeuron**)malloc(sizeof(GRU_BasicNeuron**) * input);
    this->ES_Layers[1] = (GRU_BasicNeuron**)malloc(sizeof(GRU_BasicNeuron**) * output);

    for (int i = 0; i < input; ++i) {
        this->ES_Layers[0][i] = new GRU_BasicNeuron(1);
    }

    for (int i = 0; i < output; ++i) {
        this->ES_Layers[1][i] = new GRU_BasicNeuron(lastLayerSize);
    }
}

GatedRecurrentUnit::~GatedRecurrentUnit() {
    delete[] this->hiddenLayers;
    delete[] this->ES_Layers;
}

double* GatedRecurrentUnit::load(double* input) {
    double* output = (double*)malloc(sizeof(double) * this->inputSize);

    // input neurons

    for (int i = 0; i < this->inputSize; ++i) {
        double* input_value = new double;
        *input_value = input[i];

        output[i] = ES_Layers[0][i]->load(input_value);
        delete input_value;
    }

    // hidden layer

    int lastLayerSize = this->inputSize;

    for (int i = 0; i < this->hiddenLayerSize; ++i) {
        int numOfNeurons = (lastLayerSize + this->outputSize) / 2;
        double* new_output = (double*)malloc(sizeof(double) * numOfNeurons);

        for (int n = 0; n < numOfNeurons; ++n) {
            new_output[n] = this->hiddenLayers[i][n]->load(output);
        }

        free(output);
        output = new_output;

        lastLayerSize = numOfNeurons;
    }

    // output layer

    double* new_output = (double*)malloc(sizeof(double) * this->outputSize);

    for (int i = 0; i < this->outputSize; ++i) {
        new_output[i] = this->ES_Layers[1][i]->load(output);
    }

    free(output);
    return new_output;
}
