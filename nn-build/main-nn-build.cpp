#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <filesystem>
#include <fstream>
#include <memory>
#include <windows.h>
#include <chrono>
#include <thread>

#include <nlohmann/json.hpp>

#include "assets/neural-network/neural-network.hpp"
#include "assets/nn-input-manager.hpp"
#include "assets/maths.hpp"
#include "assets/utils.hpp"

#include "core/binance/binance.hpp"

using namespace nlohmann;
using namespace std::this_thread;
using namespace std::chrono;

//

class NN_Trained {
    public:
        std::shared_ptr<NeuralNetwork> nn;
        std::vector<double> output;

        NN_Trained(std::shared_ptr<NeuralNetwork> nn, int max_score) : nn(nn), max_score(max_score), score(0) {};

        void addPoints(int points) {
            score += points;
        }

        double accuracy(void) {
            return static_cast<double>(score) / max_score;
        };

        void run(std::vector<double> input) {
            output.clear();
            output = nn->load(input);
        }

    private:
        int max_score;
        int score;

};

double getGeneralAccuracy(std::vector<NN_Trained> nn_trained) {
    double sum = 0;

    for (auto nt : nn_trained) {
        sum += nt.accuracy();
    }

    return sum / nn_trained.size();
}

//

std::vector<std::shared_ptr<NeuralNetwork>> messedNeuralNetworks(std::shared_ptr<NeuralNetwork> base, int amount) {
    std::vector<std::shared_ptr<NeuralNetwork>> nns;
    
    for (int i = 0; i < amount; ++i) {
        std::shared_ptr<NeuralNetwork> copy = base->copy();

        messNeuralNetwork(copy);

        nns.push_back(copy);
    }

    return nns;
}

void trainNeuralNetwork(std::string symbol, std::string nn_type, std::string time_type, UTC* startTime) {
    std::string nn_name = nn_type + "-" + time_type;
    std::shared_ptr<NeuralNetwork> nn = nullptr;

    std::ifstream config_file;
    json config;

    config_file.open("./config.json");
    config_file >> config;

    json nn_config = config["nn"][nn_type];

    if (!std::filesystem::exists("./" + std::string(NN_PATH) + nn_name + ".dat")) {
        int input = nn_config["input"];
        int output = nn_config["output"];
        int hidden_layers = nn_config["hidden-layers"];

        if (nn_type == "regular") {
            nn = createNeuralNetwork<NN_Regular>(input, output, hidden_layers);
        } else if (nn_type == "future") {
            nn = createNeuralNetwork<NN_FuturePrice>(input, output, hidden_layers);
        }

        saveNeuralNetwork(nn_name, nn);
    } else {
        nn = loadNeuralNetwork(nn_name);
    }

    std::string candle_time_d = nn_config["types"][time_type]["candle-time"];

    int operation_time = nn_config["types"][time_type]["operation-time"];
    CANDLE_INTERVAL_ENUM candle_time;

    for (auto _enum : CANDLE_INTERVAL_ENUMS) {
        if (_enum.interval == candle_time_d) {
            candle_time = _enum;
            break;
        }
    }
    
    // estratégia de treinamento

    int numOfOperations = 20;
    int numOfNN = 200;
    int showInfoAfter = 5;
    int currInfoTimeout = showInfoAfter;

    UTC* currTime = startTime;
    int cicle = 0;
    
    std::vector<NN_Trained> neural_networks;

    int onScore = 10;
    int max_score = numOfOperations * onScore;

    CANDLE_INTERVAL* interval = candle_time.var;

    std::vector<candle> candles = binance::getCandlesticks(symbol, *interval, currTime);

    sleep_for(seconds(5));

    while (true) {
        auto nns = messedNeuralNetworks(nn, numOfNN);
        std::shared_ptr<NeuralNetwork> bestNN = nullptr;

        neural_networks.clear();

        for (auto nn : nns) {
            neural_networks.push_back(NN_Trained(nn, max_score));
        }

        // fase de testes
        
        for (int i = 0; i < numOfOperations; ++i) {
            NNInputTrainData input;

            try {
                input = makeNNInput(candles, cicle);
            } catch (std::exception e) {
                cicle = 0;
                currTime->advance(static_cast<double>(500 * candle_time.value) / 60 / 24);
                
                candles = binance::getCandlesticks(symbol, *interval, currTime);
                sleep_for(seconds(5));
                break;
            }

            int nextCandleOffset = operation_time / candle_time.value;
            int nextCandleId = input.currCandle + nextCandleOffset;

            candle lastCandle = candles[input.currCandle];
            candle nextCandle = candles[nextCandleId];

            for (int i = 0; i < neural_networks.size(); ++i) {
                neural_networks[i].run(input.input);

                if (nn_type == "regular") {
                    int output = neural_networks[i].output[0];

                    if ((output && lastCandle.close < nextCandle.close) || (!output && lastCandle.close > nextCandle.close)) {
                        neural_networks[i].addPoints(onScore);
                    }
                } else if (nn_type == "future") {

                }
            }
            
            cicle += nextCandleOffset;

            std::shared_ptr<NeuralNetwork> bestNN = neural_networks[0].nn;
            double accuracy = neural_networks[0].accuracy();

            for (auto nn_trained : neural_networks) {
                if (nn_trained.accuracy() > accuracy) {
                    accuracy = nn_trained.accuracy();
                    bestNN = nn_trained.nn;
                }
            }

            saveNeuralNetwork(nn_name, bestNN);
            nn = bestNN;

            //

            currInfoTimeout++;

            if (currInfoTimeout >= showInfoAfter) {
                currInfoTimeout = 0;

                system("cls");

                std::cout << "Tipo de rede neural: " << nn_type << " " << time_type << "\n";
                std::cout << "Par de treinamento: " << symbol << "\n";
                std::cout << "Dia atual: "  << (currTime->print()) << "\n\n";
                std::cout << "Best Neural-Network accuracy: " << accuracy * 100 << "%" << "\n";
                std::cout << "General Accuracy (" << numOfNN << " nn's): " << getGeneralAccuracy(neural_networks) * 100 << "%";
            }
        }
    }

    saveNeuralNetwork(nn_name, nn);
}

int main(int argc, char** argv) {
    /*
    
        nn-build symbol nn-type time_type start_utc

    */

    std::cout << "Iniciando treinamento..." << "\n";

    binance::init();

    std::string symbol = std::string(argv[1]);
    std::string nn_type = std::string(argv[2]);
    std::string time_type = std::string(argv[3]);
    
    int day = std::atoi(argv[4]);
    int month = std::atoi(argv[5]);
    int year = std::atoi(argv[6]);

    trainNeuralNetwork(symbol, nn_type, time_type, UTCFormated(day, month, year));

    return 0;
}
