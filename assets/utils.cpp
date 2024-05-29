// funções/estruturas de utilidade geral

#include "utils.hpp"

#include <iostream>

//

CustomException::CustomException(const char* err_message) throw() : err_message(err_message), std::exception() {};
const char* CustomException::what(void) const throw() {
    return this->err_message;
}

//

UTC::UTC(int day, int month, int year) : day(day), month(month), year(year) {
    this->value = stod(std::to_string(year) + std::to_string(month) + std::to_string(day));
}

void UTC::advance(int days) {
    day += days;

    if (month == 2 && day > 28) {
        day -= 28;
        month++;
    } else if (month != 2 && day > 30) {
        day -= 30;
        month++;
    }

    if (month > 12) {
        month = 1;
        year++;
    }

    this->value = stod(std::to_string(year) + std::to_string(month) + std::to_string(day));
}

std::string UTC::print(void) {
    return std::to_string(day) + "/" + std::to_string(month) + "/" + std::to_string(year);
}

UTC* UTCFormated(int day, int month, int year) {
    return new UTC(day, month, year);
}
