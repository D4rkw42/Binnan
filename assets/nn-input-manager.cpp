// reduz as chamadas de função para criar as entradas da rede neural

#include "nn-input-manager.hpp"

#include "assets/maths.hpp"
#include "assets/utils.hpp"

std::vector<double> makeNNInput(std::string symbol, CANDLE_INTERVAL interval, UTC* startTime) {
    std::vector<double> input;
    auto candles = binance::getCandlesticks(symbol, interval, startTime);

    // fechamento/volume dos primeiros 6 candles

    return input;
}

NNInputTrainData makeNNInput(std::string symbol, CANDLE_INTERVAL interval, int cicle, UTC* startTime) {
    std::vector<double> input;
    candle nextCandle;

    auto candles = binance::getCandlesticks(symbol, interval, startTime);

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

    // obtendo os primeiros 6 candles (dados)

    for (candle c : t_candles) {
        input.push_back(c.close);
        input.push_back(c.open);
        input.push_back(c.low);
        input.push_back(c.high);
        input.push_back(c.volume);
    }

    //

    double averg9 = movingAverage(t_candles, 9);
    double averg12 = movingAverage(t_candles, 12);
    double averg26 = movingAverage(t_candles, 26);
    double averg30 = movingAverage(t_candles, 30);
    double averg200 = movingAverage(t_candles, 200);

    double expAverg30 = expMovingAverage(t_candles, 30);

    auto boll = bollinger(t_candles);
    double rsi = relativeStrengthIndex(t_candles);

    //

    input.push_back(averg30);
    input.push_back(averg200);

    input.push_back(expAverg30);

    // MACD
    input.push_back(averg9);
    input.push_back(averg12 - averg26);

    input.push_back(boll[0]);
    input.push_back(boll[1]);

    input.push_back(rsi);

    //

    nextCandle = candles[candles.size() + candleSelectionNum - 1];

    return NNInputTrainData {input, nextCandle};
}
