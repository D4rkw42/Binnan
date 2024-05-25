// funções/estruturas de utilidade geral

#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <string>

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
