// importantes funções matemáticas

#ifndef MATHS_H
#define MATHS_H

#include <vector>
#include <effolkronium/random.hpp>

#include "core/binance/binance.hpp"

using random = effolkronium::random_static;

//

extern const double LEAKY_RELU_CONSTANT;


//

void ReLu(std::vector<double>& values);

void LeakyReLu(std::vector<double>& values);

void sigmoid(std::vector<double>& values);

// for input

double movingAverage(std::vector<candle> candles, int period, int startAt = 0);
double expMovingAverage(std::vector<candle> candles, int period);
std::vector<candle> filterCandles(std::vector<candle> candles, int period, bool high);
double relativeStrengthIndex(std::vector<candle> candles);
double offset(std::vector<candle> candles, int period);
std::vector<double> bollinger(std::vector<candle> candles);

#endif
