#include <iostream>

#include "core/binance/binance.hpp"
#include "assets/neural-network/neural-network.hpp"
#include "assets/utils.hpp"

int main(int argc, char** argv) {
    binance::init();
    std::cout << UTCFormated(24, 12, 2024);

    return 0;
}
