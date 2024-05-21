// funções de utilidade geral

#include "utils.hpp"

std::string UTCFormated(int day, int month, int year) {
    return std::to_string(year) + "-" + std::to_string(month) + "-" + std::to_string(day);
}
