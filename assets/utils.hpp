// funções/estruturas de utilidade geral

#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <string>

// exception related

class CustomException : public std::exception {
    public:
        const char* err_message;
        CustomException(const char* err_message) throw();
        virtual char const* what(void) const throw();

};

// date related

class UTC { // utc date formated
    public:
        int value;
        int day, month, year;
        UTC(int day, int month, int year);

        void advance(int days);
        std::string print(void);

};

UTC* UTCFormated(int day, int month, int year);

#endif
