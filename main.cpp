#include <iostream>

#include "core/binance/binance.hpp"
#include "assets/neural-network/neural-network.hpp"

int main(int argc, char** argv) {
    binance::init();
    std::vector<candle> candles = binance::getCandlesticks("BTCUSDT", _3M);

    std::cout << offset(candles, 20);

    return 0;
}
