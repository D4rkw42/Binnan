// binance spot

#ifndef BINANCE_H
#define BINANCE_H

#include <string>
#include <vector>

#include <nlohmann/json.hpp>

typedef struct {
    std::string api_key;
    std::string secret_key;
} user_data;

typedef struct {
    std::string base_asset;
    std::string quote_asset;
    nlohmann::json filters;
} exchange_info;

// basic candle data

// candle intervals

typedef const std::string CANDLE_INTERVAL;

static CANDLE_INTERVAL _3M = "3m"; // 3 minutes
static CANDLE_INTERVAL _5M = "5m"; // 5 minutes
static CANDLE_INTERVAL _15M = "15m"; // 15 minutes
static CANDLE_INTERVAL _30M = "30m"; // 30 minutes
static CANDLE_INTERVAL _1H = "1h"; // 1 hour


typedef struct {
    double open, close;
    double high, low;
    double volume;
} candle;

//

static std::string api_url;
static user_data user;

//

namespace binance {
    // initialization/quit

    void init(void);

    // get spots

    exchange_info getExchangeInfo(std::string symbol);
    std::vector<candle> getCandlesticks(std::string symbol, CANDLE_INTERVAL interval);

    // post spots

}

#endif
