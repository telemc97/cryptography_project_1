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
    static int32 mod26(int32 a);

    /**
     * @brief Calculates the sum of a vector of int32 values.
     * @param values A vector of int32 numbers to be summed.
     * @return The sum of the values.
     */
    static int32 sum(const Vector(int32)& values);

    /**
     * @brief Calculates the sum of a vector of uint32 values.
     * @param values A vector of uint32 numbers to be summed.
     * @return The sum of the values.
     */
    static uint32 sum(const Vector(uint32)& values);

    /**
     * @brief Calculates the sum of a vector of float64 values.
     * @param values A vector of float64 numbers to be summed.
     * @return The sum of the values.
     */
    static float64 sum(const Vector(float64)& values);

    /**
     * @brief Calculates the average of a vector of float64 values.
     * @param values A vector of float64 numbers to be averaged.
     * @return The average of the values. Returns 0.0 if the vector is empty.
     */
    static float64 average(const Vector(float64)& values);

    /**
     * @brief Evaluates if the given integer is prime based on the Proposition from
     * excercise 1 in Cryptography project 2
     * @param number
     * @return
     */
    static bool isPrime(const String &number);

    static String generateRandomOddNumber(uint16 bits);

    /**
     * @brief Finds all divisors of a given integer.
     * @param number The integer to find divisors for.
     * @return A vector containing all divisors of the number.
     */
    static Vector(int32) findDivisors(int32 number);

    static bool isPairAmicable(int32 number_1, int32 number_2);
};

#endif //CRYPTOGRAPHY1_MATH_H