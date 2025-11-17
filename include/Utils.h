//
// Created by Tilemahos Mitroudas on 15/11/25.
//

#ifndef CRYPTOGRAPHY1_UTILS_H
#define CRYPTOGRAPHY1_UTILS_H

#include "Types.h"

class Utils {

public:
    static int8 convertGreekCharToInt(wide_char character);
    static wide_char convertIntToGreekChar(int integer);
    static int8 convertEnglishCharToInt(char c);
    static char convertIntToEnglishChar(uint8 i);

};


#endif //CRYPTOGRAPHY1_UTILS_H
