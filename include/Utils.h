#ifndef CRYPTOGRAPHY1_UTILS_H
#define CRYPTOGRAPHY1_UTILS_H

#include "Types.h"

/**
 * @class Utils
 * @brief Provides utility functions for character conversions.
 *
 * The Utils class contains static methods for converting characters to and from integer representations.
 * It supports both Greek and English alphabets.
 */
class Utils {

public:
    /**
     * @brief Converts a Greek character to its corresponding integer representation.
     *
     * This function takes a wide character (Greek) and returns an integer from 1 to 24.
     * Both uppercase and lowercase Greek letters are handled.
     *
     * @param character The Greek character to convert.
     * @return int8 The integer representation (1-24), or 0 if the character is not a Greek letter.
     */
    static int8 convertGreekCharToInt(wide_char character);

    /**
     * @brief Converts an integer to its corresponding Greek character.
     *
     * This function takes an integer (from 1 to 24) and returns the corresponding lowercase Greek character.
     * Integers outside this range will be handled gracefully.
     *
     * @param integer The integer to convert.
     * @return wide_char The corresponding Greek character, or a space for out-of-range integers.
     */
    static wide_char convertIntToGreekChar(int integer);

    /**
     * @brief Converts an English character to its corresponding integer representation (0-25).
     *
     * This function takes an English character and converts it to a zero-based integer.
     * The conversion is case-insensitive. 'a' or 'A' becomes 0, 'b' or 'B' becomes 1, and so on.
     *
     * @param c The English character to convert.
     * @return int8 The integer representation (0-25), or -1 if the character is not an English letter.
     */
    static int8 convertEnglishCharToInt(char c);

    /**
     * @brief Converts an integer (0-25) to its corresponding lowercase English character.
     *
     * This function takes an integer and returns the corresponding lowercase English character.
     * 'a' for 0, 'b' for 1, etc.
     *
     * @param i The integer to convert.
     * @return char The corresponding English character, or a space for out-of-range integers.
     */
    static char convertIntToEnglishChar(uint8 i);

    /**
     * @brief Returns the digits of an unsigned integer as a vector of unsigned integers.
     *
     * This function takes an unsigned integer and returns a vector containing its digits in order.
     * For example, if the input is 123, the function will return a vector {1, 2, 3}.
     *
     * @param number The unsigned integer to process.
     * @return Vector(uint8) A vector of the digits of the number.
     */
    static Vector(uint8) getDigits(uint64 number);

};


#endif //CRYPTOGRAPHY1_UTILS_H
