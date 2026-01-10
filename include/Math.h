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
    static BigInt findGCD(const Vector(BigInt)& numbers);

    static uint32 findGCD(const Vector(uint32)& numbers);

    /**
     * @brief Computes the value of an integer modulo 26.
     *        Ensures the result is always positive, which is essential for Vigenère cipher arithmetic.
     * @param a The integer to apply the modulo operation to.
     * @return The result of `a mod 26`, in the range [0, 25].
     */
    static int32 mod26(int32 a);

    /**
     * @brief Calculates the square root of a BigInt.
     * @param n The BigInt number.
     * @return The square root of n.
     */
    static BigInt sqrt(const BigInt& n);

    /**
     * @brief Calculates the square root of a double.
     * @param n The number.
     * @return The square root of n.
     */
    static float64 sqrt(float64 n);

    /**
     * @brief Calculates the power of a BigInt base raised to an unsigned integer exponent.
     * @param base The base.
     * @param exp The exponent.
     * @return base raised to the power of exp.
     */
    static BigInt pow(const BigInt& base, uint32 exp);

    /**
     * @brief Calculates the power of a base raised to an exponent.
     * @param base The base.
     * @param exp The exponent.
     * @return base raised to the power of exp.
     */
    static float64 pow(float64 base, float64 exp);

    /**
     * @brief Calculates (base^exp) % mod using the Square and Multiply algorithm.
     * @param base The base.
     * @param exp The exponent.
     * @param mod The modulus.
     * @return The result of (base^exp) % mod.
     */
    static BigInt squareAndMultiply(BigInt base, BigInt exp, const BigInt& mod);\

    static int32 squareAndMultiply(int32 base, int32 exp, const int32& mod);

    /**
     * @brief Calculates the modular multiplicative inverse of a modulo m.
     *        Solves for x in the congruence ax ≡ 1 (mod m).
     * @param a The number to find the inverse of.
     * @param m The modulus.
     * @return The modular multiplicative inverse of a mod m. Returns 0 if inverse does not exist.
     */
    static BigInt modInverse(BigInt a, BigInt m);

    static int32 modInverse(int32 a, int32 m);


    /**
     * @brief Calculates the absolute value of a BigInt.
     * @param n The BigInt number.
     * @return The absolute value of n.
     */
    static BigInt abs(const BigInt& n);

    /**
     * @brief Calculates the absolute value of a number.
     * @param n The number.
     * @return The absolute value of n.
     */
    static float64 abs(float64 n);

    /**
     * @brief Calculates the absolute value of an integer.
     * @param n The number.
     * @return The absolute value of n.
     */
    static int32 abs(int32 n);

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
     * @brief Evaluates if the given integer is prime.
     * @param number The BigInt number to check for primality.
     * @return True if the number is prime, false otherwise.
     */
    static bool isPrimeMacMahon(const BigInt &number);

    /**
     * @brief Evaluates if the given integer is prime using a fast probabilistic test (Miller-Rabin).
     * @param number The BigInt number to check for primality.
     * @return True if the number is probably prime, false otherwise.
     */
    static bool isPrimeQuick(const BigInt &number);

    /**
     * @brief Generates a random int32 in the range [min, max).
     * @param min The lower bound (inclusive).
     * @param max The upper bound (non-inclusive).
     * @return A random int32 value.
     */
    static int32 generateRandomInt(int32 min, int32 max);

    /**
     * @brief Generates a random BigInt with a specified number of bits.
     * @param bits The number of bits for the generated BigInt.
     * @return A random BigInt of the specified bit length.
     */
    static BigInt generateRandomBigNumber(const uint16 &bits);

    /**
     * @brief Generates a random BigInt with specified bit length and parity options.
     * @param bits The number of bits for the generated BigInt.
     * @param odd Whether the generated number can be odd.
     * @param even Whether the generated number can be even.
     * @return A random BigInt matching the specified criteria.
     */
    static BigInt generateRandomBigNumber(const uint16 &bits, const bool &odd, const bool &even);

    /**
     * @brief Generates a random odd BigInt with a specified number of bits.
     * @param bits The number of bits for the generated BigInt.
     * @return A random odd BigInt of the specified bit length.
     */
    static BigInt generateRandomBigOddNumber(const uint16 &bits);

    /**
     * @brief Generates a random even BigInt with a specified number of bits.
     * @param bits The number of bits for the generated BigInt.
     * @return A random even BigInt of the specified bit length.
     */
    static BigInt generateRandomBigEvenNumber(const uint16 &bits);

    /**
     * @brief Finds all divisors of a given integer.
     * @param number The integer to find divisors for.
     * @return A vector containing all divisors of the number.
     */
    static Vector(int32) findDivisors(const int32 &number);
    static Vector(BigInt) findDivisors(const BigInt &number);

    /**
     * @brief Checks if two numbers are amicable.
     *        Two numbers are amicable if the sum of their proper divisors are equal,
     *        and that sum equals the sum of the two numbers.
     * @param number_1 The first number.
     * @param number_2 The second number.
     * @return True if the numbers are amicable, false otherwise.
     */
    static bool isPairAmicable(const int32 &number_1, const int32 &number_2);

    /**
     * @brief Performs trial division to find the prime factors of a BigInt.
     * @param number The BigInt to factorize.
     * @return A vector of BigInt prime factors.
     */
    static Vector(BigInt) trialDivision(const BigInt &number);

    static BigInt extendedGCD(BigInt a, BigInt b, BigInt &x, BigInt &y);

    static int32 extendedGCD(int32 a, int32 b, int32 &x, int32 &y);

};

#endif //CRYPTOGRAPHY1_MATH_H