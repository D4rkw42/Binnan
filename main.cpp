#include <iostream>

#include "core/binance/binance.hpp"

int main(int argc, char** argv) {
    binance::init();
    std::vector<candle> candles = binance::getCandlesticks("BTCUSDT", _30M);

    std::cout << candles[0].open << "\n";
    std::cout << candles[0].close;

    return 0;
}
