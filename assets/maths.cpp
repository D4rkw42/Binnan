// importantes funções matemáticas

#include "maths.hpp"

#include <cstdlib>
#include <cmath>

// const double LEAKY_RELU_CONSTANT = 100000;

//

// void ReLu(std::vector<double>& values) {
//   for (double& value : values) {
//     value = (value > 0)? value : 0;
//   }
// }

double ReLu(double value) {
  return (value > 0)? value : 0;
}

double sigmoid(double value) {
  return 1.f / (1 + exp(-value));
}

// for input

double movingAverage(std::vector<candle> candles, int period, int startAt) {
    double average = 0;

    for (int i = startAt; i < period + startAt; ++i) {
        average += candles[i].close;
    }

    return average / period;
}

double expMovingAverage(std::vector<candle> candles, int period) {
    double currEMA = movingAverage(candles, period);
    double lastEMA = movingAverage(candles, period, period);

    double smooth_coef = 2.f / (period + 1);

    return currEMA * smooth_coef + lastEMA * (1 - smooth_coef);
}

std::vector<candle> filterCandles(std::vector<candle> candles, int period, bool high) {
    std::vector<candle> filtered;

    for (int i = 0; i < period; ++i) {
        if ((candles[i].close > candles[i].open && high) || (candles[i].close < candles[i].open && !high)) {
            filtered.push_back(candles[i]);
        }
    }

    return filtered;
}

double relativeStrengthIndex(std::vector<candle> candles) {
    std::vector<candle> high_candles = filterCandles(candles, 14, true);
    std::vector<candle> low_candles = filterCandles(candles, 14, false);

    double high_candlesAverg = movingAverage(high_candles, high_candles.size());
    double low_candlesAverg = movingAverage(low_candles, low_candles.size());

    double rs = high_candlesAverg / low_candlesAverg;

    return 100 - 100.f / (1 + rs);
}

double offset(std::vector<candle> candles, int period) {
    double averg = movingAverage(candles, period);
    double sum = 0;

    for (int i = 0; i < period; ++i) {
        sum += pow(candles[i].close - averg, 2);
    }

    return pow(sum / period, 0.5f);
}

std::vector<double> bollinger(std::vector<candle> candles) {
    double off = offset(candles, 20);
    double averg = movingAverage(candles, 20);

    double ub = averg + off * 2;
    double lb = averg - off * 2;

    return std::vector {ub, lb};
}
