// reduz as chamadas de função para criar as entradas da rede neural

#include "nn-input-manager.hpp"

#include <iostream>

#include "assets/maths.hpp"
#include "assets/utils.hpp"

std::vector<double> makeNNInput(std::string symbol, CANDLE_INTERVAL interval, UTC* startTime) {
    std::vector<double> input;
    auto candles = binance::getCandlesticks(symbol, interval, startTime);

    // fechamento/volume dos primeiros 6 candles

    return input;
}

NNInputTrainData makeNNInput(std::vector<candle> candles, int cicle) {
    std::vector<double> input;

    // seleção de candles para treinamento

    if (abs(-200 - cicle - 1) > candles.size()) {
        throw std::exception();
    }

    int candleSelectionNum = -200 - cicle;

    std::vector<candle> t_candles;
    int init = candles.size() + candleSelectionNum; // selecionando o candle específico

    for (int i = init; i < candles.size(); ++i) {
        t_candles.push_back(candles[i]);
    }

    // obtendo os dados

    /*

        dados dos 5 primeiros candles:
        - diferença entre a abertura e fechamento (porcentagem)
        - diferença entre a abertuta e alta máxima (porcentagem)
        - diferença entre a abertura e baixa máxima (porcentagem)

        médias móveis
        - diferença entre o preço atual e a média móvel de 9 níveis (porcentagem)
        - diferença entre o preço atual e a média móvel de 30 níveis (porcentagem)
        - diferença entre o preço atual e a média móvel de 200 níveis (porcentagem)
        - diferença entre o preço atual e a média móvel exponencial de 30 níveis (porcentagem)

        outros
        - diferença percentual entre a banda máxima e mínima do bollinger e o preço atual
        - diferença percentual entre as bandas e a média de 30 níveis
        - diferença percentual entre a média de 12 níveis e média de 26 níveis
        - rsi normal

    */

    for (int i = 0; i < 5; ++i) {
        input.push_back(t_candles[i].close / t_candles[i].open);
        input.push_back(t_candles[i].high / t_candles[i].open);
        input.push_back(t_candles[i].low / t_candles[i].open);
    }

    double price = t_candles[0].close;

    double averg9 = movingAverage(t_candles, 9);
    double averg12 = movingAverage(t_candles, 12);
    double averg26 = movingAverage(t_candles, 26);
    double averg30 = movingAverage(t_candles, 30);
    double averg200 = movingAverage(t_candles, 200);
    double expAverg30 = expMovingAverage(t_candles, 30);

    input.push_back(averg9 / price);
    input.push_back(averg30 / price);
    input.push_back(averg200 / price);
    input.push_back(expAverg30 / price);

    input.push_back(averg26 / averg12);

    std::vector<double> boll = bollinger(t_candles);
    double rsi = relativeStrengthIndex(t_candles);

    input.push_back(boll[0] / price);
    input.push_back(boll[1] / price);

    input.push_back(boll[0] / averg30);
    input.push_back(boll[1] / averg30);

    input.push_back(rsi);

    // std::cout << "\n\n";

    // for (auto v : input) {
    //     std::cout << v << " ";
    // }

    // std::cout << "\n-------------\n";

    //

    return NNInputTrainData {input, init};
}
