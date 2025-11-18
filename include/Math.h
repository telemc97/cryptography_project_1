//
// Created by Tilemahos Mitroudas on 15/11/25.
//

#ifndef CRYPTOGRAPHY1_MATH_H
#define CRYPTOGRAPHY1_MATH_H

#include "Types.h"
#include <vector>

/**
 * @brief The `Math` class provides a collection of static mathematical utility functions.
 *        These functions are used for calculations required in various cryptographic analyses.
 */
class Math {
public:
    /**
     * @brief Finds the greatest common divisor (GCD) of a vector of numbers.
     * @param numbers A vector of unsigned integers for which to find the GCD.
     * @return The greatest common divisor of the numbers in the vector. Returns 0 if the vector is empty.
     */
    static uint32 findGCD(const Vector(uint32)& numbers);

    /**
     * @brief Computes the value of an integer modulo 26.
     *        Ensures the result is always positive, which is essential for Vigenère cipher arithmetic.
     * @param a The integer to apply the modulo operation to.
     * @return The result of `a mod 26`, in the range [0, 25].
     */
    static int mod26(int a);

    /**
     * @brief Calculates the average of a vector of float64 values.
     * @param values A vector of float64 numbers to be averaged.
     * @return The average of the values. Returns 0.0 if the vector is empty.
     */
    static float64 average(const Vector(float64)& values);
};

#endif //CRYPTOGRAPHY1_MATH_H