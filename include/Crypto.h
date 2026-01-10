#ifndef CRYPTOGRAPHY1_CRYPTO_H
#define CRYPTOGRAPHY1_CRYPTO_H

#include "Types.h"

/**
 * @struct WordOccurrences
 * @brief Represents a recurring word found in a ciphertext.
 * @details This struct is used to store a word and the number of times it appears in a text,
 *          which is particularly useful in frequency analysis and the Kasiski examination.
 */
struct WordOccurrences {
    uint32 count; ///< The number of times the word occurs.
    String word;  ///< The recurring word itself.
};

/**
 * @class Crypto
 * @brief Provides a suite of static methods for cryptographic analysis and operations.
 * @details This class includes tools for classical cipher analysis, such as the Kasiski examination
 *          and Friedman test, as well as functions for encryption and decryption. All methods
 *          are static, meaning they can be called directly without creating an instance of the class.
 */
class Crypto {
public:
    /**
     * @brief Estimates the most probable key length of a polyalphabetic cipher using the Kasiski examination.
     * @details This method identifies repeated sequences of characters in the ciphertext and calculates the
     *          distances between them. The greatest common divisor (GCD) of these distances is likely
     *          to be the key length.
     * @param message The ciphertext to analyze.
     * @param min_word_length The minimum length of a recurring word to be considered for the analysis.
     * @return The estimated key length. Returns 0 if no recurring words are found.
     */
    static uint32 findKeyLengthKasiski(const String &message, uint32 min_word_length);

    /**
     * @brief Estimates the key length of a polyalphabetic cipher using the Friedman test (Index of Coincidence).
     * @details The Friedman test measures the Index of Coincidence (IC) for various possible key lengths.
     *          The IC for a monoalphabetic cipher is significantly higher than for a polyalphabetic cipher.
     *          This method finds the key length that results in the highest average IC across all columns,
     *          which is characteristic of a correctly guessed key length.
     * @param message The ciphertext to analyze.
     * @param max_key_length The maximum key length to test against.
     * @return The estimated key length. Returns 1 if no optimal key length is found, as a fallback.
     */
    static uint32 findKeyLengthFriedman(const String &message, uint32 max_key_length);

    /**
     * @brief Derives a potential key for a Vigenère cipher through frequency analysis.
     * @details This function assumes the underlying plaintext is English and that the most frequent character
     *          in each column of the ciphertext (when arranged by key length) corresponds to 'E'.
     *          By calculating the shift for each column, a probable key is derived.
     * @param message The ciphertext to analyze.
     * @param key_length The length of the key to derive.
     * @return The derived key as a string.
     */
    static String getKeyWithFrequencyAnalysis(const String &message, uint32 key_length);

    /**
     * @brief Decrypts a Vigenère-encrypted message using a provided key.
     * @details This method applies the Vigenère cipher decryption algorithm, subtracting the key character
     *          value from the ciphertext character value (modulo 26) to recover the plaintext.
     * @param message The ciphertext to decrypt.
     * @param key The key to use for decryption.
     * @return The decrypted message (plaintext).
     */
    static String vigenereDecipher(const String &message, String key);

    /**
     * @brief Decrypts a 16-bit message that was encrypted with a specific linear transformation.
     * @details The decryption formula is the inverse of the encryption function. By analyzing the
     *          linear feedback shift register (LFSR) properties of the encryption, the inverse
     *          transformation is found to be \f$ m = c \oplus (c \ll 6) \oplus (c \ll 10) \oplus (c \ll 12) \f$.
     * @param encrypted_msg The 16-bit ciphertext to decrypt.
     * @return The recovered 16-bit plaintext.
     */
    static uint16 decrypt16bit(uint16 encrypted_msg);

    /**
     * @brief Encrypts a 16-bit message using a specific linear transformation.
     * @details The encryption is defined by the formula \f$ c = m \oplus (m \ll 6) \oplus (m \ll 10) \f$.
     *          This is a form of linear feedback shift register (LFSR) encryption where the ciphertext
     *          is a linear combination of the plaintext bits.
     * @param decrypted_msg The original 16-bit plaintext to encrypt.
     * @return The resulting 16-bit ciphertext.
     */
    static uint16 encrypt16bit(uint16 decrypted_msg);

    /**
     * @brief Generates a random key of the same length as the message.
     * * @details
     * According to Shannon's Perfect Secrecy theorem (Theorem 2.9.1),
     * the key must be chosen uniformly at random and be as long as the message.
     * * @param length The number of 5-bit blocks (characters) needed.
     * @return std::vector<int> A vector of random integers (0-31).
     */
    static String generateOTPKey(size_t length, const String &charset);

    /**
     * @brief Encrypts a plaintext message using a string key.
     * * @details
     * Converts both plaintext and key characters to their 5-bit integer values
     * and performs bitwise XOR. Formula: \f$ c = m \oplus k \f$.
     * @param plaintext The message to encrypt.
     * @param key The random key string (must be same length as plaintext).
     * @return std::vector<int> The encrypted ciphertext as a vector of integers.
     */
    static String encrypt(const String &plaintext, const String &key);

    /**
     * @brief Decrypts a ciphertext using the string key.
     * * @details
     * Performs the inverse operation (XOR).
     * Formula: \f$ m = c \oplus k \f$.
     * * @param ciphertext The vector of encrypted integers.
     * @param key The key string used for encryption.
     * @return std::string The recovered plaintext string.
     */
    static String decrypt(const String &ciphertext, const String &key);

    /**
     * @brief Counts the number of differing bits between two strings.
     * @param data1 The first string.
     * @param data2 The second string.
     * @return The number of bits that are different between the two strings.
     */
    static int32 countDiffBits(const String& data1, const String& data2);

    /**
     * @brief Encrypts a plaintext using AES in ECB mode.
     * @param key The encryption key.
     * @param plaintext The plaintext to encrypt.
     * @return The encrypted ciphertext.
     */
    static String encryptECB(const String& key, const String& plaintext);

    /**
     * @brief Encrypts a plaintext using AES in CBC mode.
     * @param key The encryption key.
     * @param iv The initialization vector.
     * @param plaintext The plaintext to encrypt.
     * @return The encrypted ciphertext.
     */
    static String encryptCBC(const String& key, const String& iv, const String& plaintext);

    /**
     * @brief
     * @param number The BigInt to calculate the sum of divisors for.
     * @return The sum of all divisors of the number.
     */
    static BigInt calculateM1(const BigInt &number);

    /**
     * @brief
     * @param number The BigInt used as the upper bound in the summation.
     * @return The calculated value M2.
     */
    static BigInt calculateM2(const BigInt &number);


    static bool wienerAttack(const BigInt &N, const BigInt &e, BigInt &out_private_key, BigInt &out_q, BigInt &out_p);

private:
    /**
     * @brief Finds the most frequent alphabetic character in a string.
     * @details This function is case-insensitive and is typically used in frequency analysis to guess
     *          which character corresponds to the most common letter in a language (e.g., 'E' in English).
     * @param text The string to analyze.
     * @return The most frequent character. Returns a space (' ') if no alphabetic characters are found.
     */
    static char findMostFrequentCharInString(const String& text);

    /**
     * @brief Transposes a ciphertext matrix to align characters by key position.
     * @details This method organizes the ciphertext into columns based on the key length and then
     *          reconstructs them into rows. This is not a standard cryptographic operation but can
     *          be useful for specific analytical approaches.
     * @param message The ciphertext to process.
     * @param keyLength The assumed length of the encryption key.
     * @return A vector of strings, where each string is a reconstructed row.
     */
    static Vector(String) splitEncryptedMessageReturnRows(const String &message, uint32 keyLength);

    /**
     * @brief Splits a ciphertext into columns based on the key length.
     * @details This is a crucial step for frequency analysis of polyalphabetic ciphers. Each column
     *          contains characters that were encrypted with the same key character, forming a simple
     *          monoalphabetic substitution cipher that can be broken individually.
     * @param message The ciphertext to split.
     * @param keyLength The assumed length of the encryption key.
     * @return A vector of strings, where each string represents a column of the ciphertext.
     */
    static Vector(String) splitEncryptedMessageReturnColumns(const String &message, uint32 keyLength);

    /**
     * @brief Finds all recurring words of a specified minimum length in a text.
     * @details This is the core of the Kasiski examination. The distances between these recurring
     *          words can reveal the key length of a polyalphabetic cipher.
     * @param message The text to search within.
     * @param minLength The minimum length of words to search for.
     * @return A vector of `WordOccurrences` structs, detailing each recurring word and its count.
     */
    static Vector(WordOccurrences) findRecurringWords(const String &message, uint32 minLength);

    /**
     * @brief Calculates the distances between all occurrences of a specific word.
     * @details Used in the Kasiski examination, the GCD of these distances provides a strong
     *          indicator of the key length.
     * @param message The text to search within.
     * @param word The word for which to find occurrence distances.
     * @return A vector of distances between successive occurrences of the word.
     */
    static Vector(uint32) findDistances(const String &message, const String& word);

    /**
     * @brief Calculates the Index of Coincidence (IC) for a given text.
     * @details The IC measures the probability that two randomly selected letters from a text are identical.
     *          It is a powerful tool for distinguishing monoalphabetic from polyalphabetic ciphers and is
     *          the foundation of the Friedman test for finding the key length.
     * @param text The text for which to calculate the IC.
     * @return The calculated Index of Coincidence as a float.
     */
    static float32 calculateIC(const String& text);

};

#endif //CRYPTOGRAPHY1_CRYPTO_H
