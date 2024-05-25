// binance spot

#include "binance.hpp"

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cpr/cpr.h>

using namespace std;
using namespace nlohmann;

CANDLE_INTERVAL _3M = "3m"; // 3 minutes
CANDLE_INTERVAL _5M = "5m"; // 5 minutes
CANDLE_INTERVAL _15M = "15m"; // 15 minutes
CANDLE_INTERVAL _30M = "30m"; // 30 minutes
CANDLE_INTERVAL _1H = "1h"; // 1 hour

std::vector<CANDLE_INTERVAL_ENUM> CANDLE_INTERVAL_ENUMS = {
    {"_3M", 3, &_3M},
    {"_5M", 5, &_5M},
    {"_15M", 15, &_15M},
    {"_30M", 30, &_30M},
    {"_1H", 60, &_1H}
};

std::string api_url;
user_data user;

void binance::init(void) {
    ifstream config_file("./config.json");
    json config;

    config_file >> config;

    //

    bool using_testnet = config["using-testnet"];

    if (!using_testnet) {
        user = user_data {config["user"]["api-key"], config["user"]["secret-key"]};
        api_url = config["api"]["url"];
    } else {
        user = user_data {
            config["user"]["testnet"]["api-key"],
            config["user"]["testnet"]["secret-key"]
        };

        api_url = config["api"]["testnet"]["url"];
    }
}

//

std::vector<std::string> binance::getExchangeList(void) {
    cpr::Response response = cpr::Get(cpr::Url {api_url + "/exchangeInfo"});

    if (response.status_code == 200) {
        json res = json::parse(response.text);
        std::vector<std::string> list;

        json exchange_list = res["symbols"];

        for (auto i_list = exchange_list.begin(); i_list < exchange_list.end(); ++i_list) {
            json lst = *i_list;
            list.push_back(lst["symbol"]);
        }

        return list;
    }
}

exchange_info binance::getExchangeInfo(std::string symbol) {
    cpr::Response response = cpr::Get(
        cpr::Url {api_url + "/exchangeInfo"},
        cpr::Parameters {{"symbol", symbol}}
    );

    if (response.status_code == 200) {
        json res = json::parse(response.text);
        exchange_info info;

        info.base_asset = res["symbols"][0]["baseAsset"];
        info.quote_asset = res["symbols"][0]["quoteAsset"];

        json filters = res["symbols"][0]["filters"];

        for (auto i_filter = filters.begin(); i_filter < filters.end(); ++i_filter) {
            json f = *i_filter;
            info.filters[f["filterType"]] = f;
        }

        return info;
    }
}

std::vector<candle> binance::getCandlesticks(std::string symbol, CANDLE_INTERVAL interval, UTC* startTime) {
    cpr::Parameters parameters = {
        {"symbol", symbol},
        {"interval", interval}
    };

    if (startTime != nullptr) {
        parameters.Add(cpr::Parameter("startTime", to_string(startTime->value)));
    }

    cpr::Response response = cpr::Get(cpr::Url {api_url + "/klines"}, parameters);

    if (response.status_code == 200) {
        json res = json::parse(response.text);
        std::vector<candle> candles;

        for (auto i_candle = res.begin(); i_candle < res.end(); ++i_candle) {
            json candle_data = *i_candle;
            candle candle;

            candle.open = stod(std::string(candle_data[1]).c_str());
            candle.high = stod(std::string(candle_data[2]).c_str());
            candle.low = stod(std::string(candle_data[3]).c_str());
            candle.close = stod(std::string(candle_data[4]).c_str());
            candle.volume = stod(std::string(candle_data[5]).c_str());

            candles.insert(candles.begin(), candle);
        }

        return candles;
    };
}
