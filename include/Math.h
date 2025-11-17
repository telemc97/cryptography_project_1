//
// Created by Tilemahos Mitroudas on 15/11/25.
//

#ifndef CRYPTOGRAPHY1_MATH_H
#define CRYPTOGRAPHY1_MATH_H

#include "Types.h"
#include <vector>

class Math {
public:
    static uint32 findGCD(const Vector(uint32)& numbers);
    static int mod26(int a);
};

#endif //CRYPTOGRAPHY1_MATH_H