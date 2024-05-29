// Rede Gathed Recurrent Unit (GRU)

#ifndef GATED_RECURRENT_UNIT_HPP
#define GATED_RECURRENT_UNIT_HPP

extern const int MAX_RANDOM_WEIGHT;
extern const int MAX_RANDOM_BIAS;

//

class GRU_HiddenLayerNeuron {
    public:
        double *Wz, *Wr, *Wh; // pesos para cada porta (cálculo com x)
        double Uz, Ur, Uh; // pesos para cada porta (cálculo com o estado oculto anterior)
        double Bz, Br, Bh; // bias para cada porta

        double* weights; // weights para ponderagem final
        double bias; // bias para ponderagem final

        double ht_1; // estado oculto anterior

        int inputSize; // tamanho das informações que percorrem o neurônio

        GRU_HiddenLayerNeuron(int input);
        ~GRU_HiddenLayerNeuron();

        // operações

        double* calculateGate(double* input, double* weights, double uWeight, double bias); // calcula a porta de atualização ou de reset
        double* candidateGate(double* input); // calcula o estado candidato

        double load(double* input); // calcula a partir das entradas

};

class GRU_BasicNeuron {
    public:
        double* weights;
        double bias;

        int inputSize;

        GRU_BasicNeuron(int input);
        ~GRU_BasicNeuron();

        double load(double* input);

};

class GatedRecurrentUnit {
    public:
        GRU_BasicNeuron*** ES_Layers;
        GRU_HiddenLayerNeuron*** hiddenLayers;

        int inputSize, outputSize, hiddenLayerSize;

        GatedRecurrentUnit(int input, int output, int hidden_layers);
        GatedRecurrentUnit(void) {};

        ~GatedRecurrentUnit();

        double* load(double* input);

};

#endif
