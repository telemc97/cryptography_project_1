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
     * @brief Converts a character to its corresponding integer representation based on a charset.
     *
     * This function takes a character and converts it to a zero-based integer based on its position in the provided charset.
     * The conversion is case-insensitive.
     *
     * @param c The character to convert.
     * @param charset The character set to use for the conversion. Defaults to the English alphabet.
     * @return int8 The integer representation, or -1 if the character is not in the charset.
     */
    static int8 convertCharToInt(char c, const String& charset = "abcdefghijklmnopqrstuvwxyz");

    /**
     * @brief Converts an integer to its corresponding character based on a charset.
     *
     * This function takes an integer and returns the corresponding character from the charset.
     *
     * @param i The integer to convert.
     * @param charset The character set to use for the conversion. Defaults to the English alphabet.
     * @return char The corresponding character, or a space for out-of-range integers.
     */
    static char convertIntToChar(uint8 i, const String& charset = "abcdefghijklmnopqrstuvwxyz");

    /**
     * @brief Returns the digits of an unsigned integer as a vector of unsigned integers.
     *
     * This function takes an unsigned integer and returns a vector containing its digits in order.
     * For example, if the input is 123, the function will return a vector {1, 2, 3}.
     *
     * @param number The unsigned integer to process.
     * @return Vector(uint8) A vector of the digits of the number.
     */
    static Vector(uint8) getDigits(const uint32 &number);

    /**
     * @brief Transposes a vector of strings.
     *
     * This function takes a vector of strings and transposes it. The first character of every string
     * of the vector will comprise the first string of the transposed vector.
     *
     * @param string_vector The vector of strings to transpose.
     * @return Vector(String) The transposed vector of strings.
     */
    static Vector(String) transposeVectorString(const Vector(String)& string_vector);

    /**
     * @brief Flattens a vector of strings into a single string.
     *
     * This function takes a vector of strings and concatenates them into a single string.
     *
     * @param string_vector The vector of strings to flatten.
     * @return String The flattened string.
     */
    static String flatten(const Vector(String)& string_vector);

    /**
     * @brief Converts a string to its string representation of bits.
     *
     * This function takes a string and returns a string representing its bits.
     *
     * @param value The string to convert.
     * @return String A string representing the bits of the data.
     */
    static String toBitString(const String& value);

    /**
     * @brief Converts an integer to a vector of its bits.
     *
     * This function takes an integer and returns a vector of uint8_t, where each
     * element is a bit (0 or 1). The bits are ordered from most significant to least significant.
     *
     * @param value The integer to convert.
     * @return Vector(uint8) A vector representing the bits of the integer.
     */
    static Vector(int32) intToBits(const int32 &value);

    /**
     * @brief Generates a random string from a given character set.
     * @param length The desired length of the string.
     * @param charset The set of characters to choose from.
     * @return A string containing random characters from the charset.
     */
    static String generateRandomString(data_size length, const String& charset);
};


#endif //CRYPTOGRAPHY1_UTILS_H
