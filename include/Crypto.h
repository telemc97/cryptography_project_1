#ifndef CRYPTOGRAPHY1_CRYPTO_H
#define CRYPTOGRAPHY1_CRYPTO_H

#include "Types.h"

/**
 * @brief Represents a recurring word found in the ciphertext.
 */
struct WordOccurrences {
    uint32 count; ///< The number of times the word occurs.
    String word;  ///< The recurring word itself.
};

/**
 * @brief The `Crypto` class provides functionality for cryptographic analysis,
 *        including methods for analyzing ciphertext to determine key lengths
 *        and decrypt messages.
 */
class Crypto {
public:
    /**
     * @brief Constructs a Crypto object with the given encrypted message.
     * @param message The encrypted message to be analyzed.
     */
    Crypto(String message);

    /**
     * @brief Finds recurring words of a minimum length in the encrypted message.
     *        Useful for Kasiski examination.
     * @param minLength The minimum length of words to search for.
     * @return A vector of `WordOccurrences` detailing the recurring words and their counts.
     */
    Vector(WordOccurrences) findRecurringWords(uint32 minLength);

    /**
     * @brief Calculates the distances between occurrences of a specific word in the message.
     *        Used in Kasiski examination to find potential key lengths.
     * @param word The word for which to find occurrence distances.
     * @return A vector of distances between successive occurrences of the word.
     */
    Vector(uint32) findDistances(const String& word) const;

    /**
     * @brief Determines the most probable key length using the Kasiski examination method.
     * @param min_word_length The minimum length of a word to be considered for the analysis.
     * @return The estimated key length. Returns 0 if no recurring words are found.
     */
    uint32 findKeyLengthKasiski(const uint32 min_word_length);

    /**
     * @brief Splits the encrypted message into rows based on a given key length by transposing the columns.
     *        This function first splits the message into columns and then flips the matrix
     *        to reconstruct the original message blocks.
     * @param keyLength The assumed length of the encryption key.
     * @return A vector of strings, where each string is a reconstructed row (block) of the ciphertext.
     */
    Vector(String) splitEncryptedMessageReturnRows(uint32 keyLength) const;

    /**
     * @brief Splits the encrypted message into columns based on the given key length.
     *        Each string in the returned vector represents a column of characters
     *        that would have been encrypted with the same key character.
     *        This is crucial for methods like the Friedman test.
     * @param keyLength The assumed length of the encryption key.
     * @return A vector of strings, where each string represents a column of the ciphertext.
     */
    Vector(String) splitEncryptedMessageReturnColumns(uint32 keyLength) const;

    /**
     * @brief Decrypts the encrypted message using a provided key.
     * @param key The key used for decryption.
     * @return The decrypted message.
     */
    String decryptMessageWithKey(String key);

    /**
     * @brief Estimates the key length using the Friedman test (Index of Coincidence method).
     * @param max_key_length The maximum key length to test.
     * @return The estimated key length. Returns 1 if no optimal key length is found.
     */
    uint32 findKeyLengthFriedman(uint32 max_key_length);

    /**
     * @brief Derives a potential key by performing frequency analysis on the columns of the ciphertext.
     *        Assumes the most frequent character in each column corresponds to 'E' in the plaintext.
     * @param key_length The length of the key to derive.
     * @return The derived key as a string.
     */
    String getKeyWithFrequencyAnalysis(uint32 key_length);

    /**
     * @brief Finds the most frequent alphabetic character in a given string, ignoring case.
     * @param text The string to analyze.
     * @return The most frequent alphabetic character in the string. Returns a space (' ')
     *         if the string contains no alphabetic characters.
     */
    char findMostFrequentCharInString(const String& text) const;

private:
    String message; ///< The encrypted message stored for analysis.

    /**
     * @brief Calculates the Index of Coincidence (IC) for a given text.
     *        The IC is a measure of how likely it is that two randomly chosen letters
     *        from the text will be the same. Used in cryptanalysis, particularly
     *        for the Friedman test.
     * @param text The text for which to calculate the IC.
     * @return The calculated Index of Coincidence as a float32.
     */
    float32 calculateIC(const String& text);
};

#endif //CRYPTOGRAPHY1_CRYPTO_H
