// reduz as chamadas de função para criar as entradas da rede neural

#ifndef NN_INPUT_MANAGER_H
#define NN_INPUT_MANAGER_H

#include <vector>
#include <string>

#include "assets/utils.hpp"

#include "core/binance/binance.hpp"

//

typedef struct { // retornado pela função de input para treino
    std::vector<double> input;
    candle nextCandle;
} NNInputTrainData;

//

/*

    symbol -> par de moedas a ser obtidos os dados
    from -> data de início da pesquisa
    to -> data de fim da pesquisa

*/

// para produção
std::vector<double> makeNNInput(std::string symbol, CANDLE_INTERVAL interval, UTC* startTime = nullptr);

// para treinamento
NNInputTrainData makeNNInput(std::string symbol, CANDLE_INTERVAL interval, int cicle, UTC* startTime = nullptr);

#endif
