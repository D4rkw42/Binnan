// binance spot

#ifndef BINANCE_H
#define BINANCE_H

#include <string>
#include <vector>

#include <nlohmann/json.hpp>

#include "assets/utils.hpp"

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

typedef std::string CANDLE_INTERVAL;

extern CANDLE_INTERVAL _3M; // 3 minutes
extern CANDLE_INTERVAL _5M; // 5 minutes
extern CANDLE_INTERVAL _15M; // 15 minutes
extern CANDLE_INTERVAL _30M; // 30 minutes
extern CANDLE_INTERVAL _1H; // 1 hour

typedef struct {
    CANDLE_INTERVAL interval;
    int value;
    CANDLE_INTERVAL* var;
} CANDLE_INTERVAL_ENUM;

extern std::vector<CANDLE_INTERVAL_ENUM> CANDLE_INTERVAL_ENUMS; // equivalente dos enums em número


typedef struct {
    double open, close;
    double high, low;
    double volume;
} candle;

//

extern std::string api_url;
extern user_data user;

//

namespace binance {
    // initialization/quit

    void init(void);

    // get spots

    std::vector<std::string> getExchangeList(void);
    exchange_info getExchangeInfo(std::string symbol);
    std::vector<candle> getCandlesticks(std::string symbol, CANDLE_INTERVAL interval, UTC* startTime = nullptr);

    // post spots

}

#endif
