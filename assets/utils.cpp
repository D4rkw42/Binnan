// funções/estruturas de utilidade geral

#include "utils.hpp"

UTC::UTC(int day, int month, int year) {
    this->value = stod(std::to_string(year) + std::to_string(month) + std::to_string(day));
}

UTC* UTCFormated(int day, int month, int year) {
    return new UTC(day, month, year);
}
