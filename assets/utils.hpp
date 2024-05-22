// funções/estruturas de utilidade geral

#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <string>

// date related

class UTC { // utc date formated
    public:
        int value;
        UTC(int day, int month, int year);

};

UTC* UTCFormated(int day, int month, int year);

#endif
