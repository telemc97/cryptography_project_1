#include "Crypto.h"
#include <iostream>
#include <random>
#include <algorithm>
#include "Math.h"
#include "Utils.h"

#include <openssl/aes.h>
#include <openssl/rand.h>
#include <openssl/evp.h>

Vector(WordOccurrences) Crypto::findRecurringWords(const String &message, const uint32 minLength) {
    if (message.length() < minLength || minLength == 0) {
        return {};
    }

    // 1. Generate all substrings of length minLength
    Vector(String) substrings;
    for (uint32 i = 0; i <= message.length() - minLength; ++i) {
        substrings.push_back(message.substr(i, minLength));
    }

    // 2. Sort to group identical substrings
    std::sort(substrings.begin(), substrings.end());

    // 3. Count occurrences and identify recurring ones
    Vector(WordOccurrences) recurringWords;
    if (substrings.empty()) {
        return recurringWords;
    }

    String currentWord = substrings[0];
    uint32 currentCount = 1;

    for (size_t i = 1; i < substrings.size(); ++i) {
        if (substrings[i] == currentWord) {
            currentCount++;
        } else {
            if (currentCount > 1) {
                recurringWords.push_back({currentCount, currentWord});
            }
            currentWord = substrings[i];
            currentCount = 1;
        }
    }
    if (currentCount > 1) {
        recurringWords.push_back({currentCount, currentWord});
    }
    // 4. Sort the results by count in descending order
    std::sort(recurringWords.begin(), recurringWords.end(), [](const WordOccurrences& a, const WordOccurrences& b) {
        return a.count > b.count;
    });

    return recurringWords;
}

Vector(uint32) Crypto::findDistances(const String &message, const String& word) {
    Vector(uint32) distances;
    Vector(uint32) occurrences;

    for (uint32 i = 0; i + word.length() <= message.length(); ++i) {
        if (message.substr(i, word.length()) == word) {
            occurrences.push_back(i);
        }
    }

    for (uint32 i = 1; i < occurrences.size(); ++i) {
        distances.push_back(occurrences[i] - occurrences[i-1]);
    }

    return distances;
}

Vector(String) Crypto::splitEncryptedMessageReturnRows(const String &message, uint32 keyLength) {
    if (keyLength == 0) {
        return {};
    }

    Vector(String) columns = splitEncryptedMessageReturnColumns(message, keyLength);
    return Utils::transposeVectorString(columns);
}

Vector(String) Crypto::splitEncryptedMessageReturnColumns(const String &message, const uint32 keyLength) {
    Vector(String) columns(keyLength); // Initialize with keyLength empty strings

    if (keyLength == 0) {
        return {}; // Handle invalid keyLength
    }

    for (uint32 i = 0; i < message.length(); ++i) {
        columns[i % keyLength] += message[i];
    }

    return columns;
}

uint32 Crypto::findKeyLengthKasiski(const String &message, const uint32 min_word_length) {
    Vector(WordOccurrences) occurrences = findRecurringWords(message, min_word_length);
    if (occurrences.empty()) {
        return 0; // Or handle error appropriately
    }
    Vector(uint32) word_distances = findDistances(message, occurrences[0].word);
    uint32 key_lenght = Math::findGCD(word_distances);
    return key_lenght;
}

char Crypto::findMostFrequentCharInString(const String& text) {
    Map(char, int) charCounts;
    int maxCount = 0;
    char mostFrequent = ' '; // Default to space if no alphabetic chars

    for (char c : text) {
        if (std::isalpha(c)) {
            char upper_c = std::toupper(c);
            charCounts[upper_c]++;
            if (charCounts[upper_c] > maxCount) {
                maxCount = charCounts[upper_c];
                mostFrequent = upper_c;
            }
        }
    }
    return mostFrequent;
}

String Crypto::vigenereDecipher(const String &message, const String key) {
    String decrypted_message;
    decrypted_message.reserve(message.length());

    for (size_t i = 0; i < message.length(); ++i) {
        const int8 encrypted_char = Utils::convertCharToInt(message[i]);
        const int8 key_char = Utils::convertCharToInt(key[i % key.length()]);

        if (encrypted_char != -1) { // Check if the character is a letter
            const char decrypted_char = Utils::convertIntToChar(Math::mod26(encrypted_char - key_char));
            decrypted_message += decrypted_char;
        } else {
            // If the character is not a letter, append it as is.
            decrypted_message += message[i];
        }
    }

    return decrypted_message;
}

float32 Crypto::calculateIC(const String& text) {
    // Filter out non-alphabetic characters and convert to uppercase for consistent counting
    String filteredText;
    for (char c : text) {
        if (std::isalpha(c)) {
            filteredText += std::toupper(c);
        }
    }

    if (filteredText.length() < 2) {
        return 0.0; // Not enough characters to calculate IC
    }

    Map(char, int) charCounts;
    for (char c : filteredText) {
        charCounts[c]++;
    }

    float64 sum_fi_minus_1 = 0.0;
    for (const auto& pair : charCounts) {
        int fi = pair.second;
        sum_fi_minus_1 += (float64)fi * (fi - 1.0);
    }

    float64 N = filteredText.length();
    if (N * (N - 1) == 0) {
        return 0.0; // Avoid division by zero if N is 0 or 1
    }

    return sum_fi_minus_1 / (N * (N - 1));
}

uint32 Crypto::findKeyLengthFriedman(const String &message, const uint32 max_key_length) {
    uint32  best_key_length = 0;
    const float64 english_ic = 0.067;
    float64 min_ic_difference = 1.0;

    for (uint32 key_length = 2; key_length < max_key_length; key_length++) {

        Vector(String) splitted_message_columns = splitEncryptedMessageReturnColumns(message, key_length);

        Vector(float64) coincidence_indices;
        for (const String& column : splitted_message_columns) {
            coincidence_indices.push_back(calculateIC(column));
        }

        if (!coincidence_indices.empty()) {
            float64 average_ic = Math::average(coincidence_indices);
            float64 ic_difference = std::abs(average_ic - english_ic);

            if (ic_difference < min_ic_difference) {
                min_ic_difference = ic_difference;
                best_key_length = key_length;
            }
        }
    }

    if (best_key_length == 0) {
        return 1;
    }

    return best_key_length;
}

String Crypto::getKeyWithFrequencyAnalysis(const String &message, uint32 key_length) {
    if (key_length == 0) {
        return "";
    }
    const Vector(String) text_columns = splitEncryptedMessageReturnColumns(message, key_length);
    String key;
    key.reserve(key_length);
    for (const auto &column : text_columns) {
        char char_to_append;
        if (column.empty()) {
            char_to_append = '?';
        } else {
            const char most_frequent_english_char = 'E';
            const char most_frequent_in_column = findMostFrequentCharInString(column);
            if (most_frequent_in_column == ' ') {
                // No alphabetic characters in the column
                char_to_append = '?';
            } else {
                // Calculate the shift
                const int8 shift = Utils::convertCharToInt(most_frequent_in_column) - Utils::convertCharToInt(most_frequent_english_char);
                char_to_append = Utils::convertIntToChar(Math::mod26(shift));
            }
        }
        key += char_to_append;
    }
    return key;
}

uint16 Crypto::decrypt16bit(const uint16 encrypted_msg) {
    // m = c ^ (c << 6) ^ (c << 10) ^ (c << 12)
    return encrypted_msg ^ (static_cast<uint16>(encrypted_msg << 6))
                         ^ (static_cast<uint16>(encrypted_msg << 10))
                         ^ (static_cast<uint16>(encrypted_msg << 12));
}

uint16 Crypto::encrypt16bit(const uint16 decrypted_msg) {
    return decrypted_msg ^ (static_cast<uint16>(decrypted_msg << 6)) ^ (static_cast<uint16>(decrypted_msg << 10));
}

String Crypto::generateOTPKey(data_size length, const String &charset) {
    String key;
    key.reserve(length);
    // Setup random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, charset.length() - 1);

    for (data_size i = 0; i < length; ++i) {
        int random_index = distrib(gen);
        key += charset[random_index];
    }
    return key;
}

String Crypto::encrypt(const String &plaintext, const String &key) {
    if (plaintext.length() != key.length()) {
        throw std::length_error("Key length must match message length.");
    }
    String ciphertext;
    ciphertext.reserve(plaintext.length());

    for (size_t i = 0; i < plaintext.length(); ++i) {
        ciphertext += plaintext[i] ^ key[i];
    }

    return ciphertext;
}

String Crypto::decrypt(const String &ciphertext, const String &key) {
    if (ciphertext.length() != key.length()) {
        throw std::length_error("Key length must match ciphertext length.");
    }
    String plaintext;
    plaintext.reserve(ciphertext.length());
    for (size_t i = 0; i < ciphertext.length(); ++i) {
        plaintext += ciphertext[i] ^ key[i];
    }

    return plaintext;
}

int32 Crypto::countDiffBits(const String& data1, const String& data2) {
    if (data1.length() != data2.length()) {
        throw std::length_error("Input strings must have the same length.");
    }

    int32 diff_bits = 0;
    for (size_t i = 0; i < data1.length(); ++i) {
        // XOR the bytes. The '1's in the result are the differing bits.
        unsigned char xor_val = data1[i] ^ data2[i];

        // Count the '1's in the byte (using a simple loop or Kernighan's algorithm)
        while (xor_val > 0) {
            xor_val &= (xor_val - 1);
            diff_bits++;
        }
    }
    return diff_bits;
}

String Crypto::encryptECB(const String& key, const String& plaintext) {
    if (key.length() != 16) {
        throw std::length_error("Key must be 16 bytes for AES-128.");
    }

    EVP_CIPHER_CTX *ctx;
    int len;
    int ciphertext_len;

    // Create and initialise the context
    if(!(ctx = EVP_CIPHER_CTX_new()))
        throw std::runtime_error("Failed to create new EVP_CIPHER_CTX");

    // Initialise the encryption operation.
    if(1 != EVP_EncryptInit_ex(ctx, EVP_aes_128_ecb(), NULL, reinterpret_cast<const unsigned char*>(key.c_str()), NULL))
        throw std::runtime_error("Failed to initialize encryption");

    String ciphertext;
    ciphertext.resize(plaintext.length() + AES_BLOCK_SIZE); // Make room for padding

    // Provide the message to be encrypted, and obtain the encrypted output.
    if(1 != EVP_EncryptUpdate(ctx, reinterpret_cast<unsigned char*>(&ciphertext[0]), &len, reinterpret_cast<const unsigned char*>(plaintext.c_str()), plaintext.length()))
        throw std::runtime_error("Failed to update encryption");
    ciphertext_len = len;

    // Finalise the encryption.
    if(1 != EVP_EncryptFinal_ex(ctx, reinterpret_cast<unsigned char*>(&ciphertext[0]) + len, &len))
        throw std::runtime_error("Failed to finalize encryption");
    ciphertext_len += len;

    // Clean up
    EVP_CIPHER_CTX_free(ctx);

    ciphertext.resize(ciphertext_len);
    return ciphertext;
}

String Crypto::encryptCBC(const String& key, const String& iv, const String& plaintext) {
    if (key.length() != 16) {
        throw std::length_error("Key must be 16 bytes for AES-128.");
    }
    if (iv.length() != 16) {
        throw std::length_error("IV must be 16 bytes for AES-128.");
    }

    EVP_CIPHER_CTX *ctx;
    int len;
    int ciphertext_len;

    // Create and initialise the context
    if(!(ctx = EVP_CIPHER_CTX_new()))
        throw std::runtime_error("Failed to create new EVP_CIPHER_CTX");

    // Initialise the encryption operation.
    if(1 != EVP_EncryptInit_ex(ctx, EVP_aes_128_cbc(), NULL, reinterpret_cast<const unsigned char*>(key.c_str()), reinterpret_cast<const unsigned char*>(iv.c_str())))
        throw std::runtime_error("Failed to initialize encryption");

    String ciphertext;
    ciphertext.resize(plaintext.length() + AES_BLOCK_SIZE); // Make room for padding

    // Provide the message to be encrypted, and obtain the encrypted output.
    if(1 != EVP_EncryptUpdate(ctx, reinterpret_cast<unsigned char*>(&ciphertext[0]), &len, reinterpret_cast<const unsigned char*>(plaintext.c_str()), plaintext.length()))
        throw std::runtime_error("Failed to update encryption");
    ciphertext_len = len;

    // Finalise the encryption.
    if(1 != EVP_EncryptFinal_ex(ctx, reinterpret_cast<unsigned char*>(&ciphertext[0]) + len, &len))
        throw std::runtime_error("Failed to finalize encryption");
    ciphertext_len += len;

    // Clean up
    EVP_CIPHER_CTX_free(ctx);

    ciphertext.resize(ciphertext_len);
    return ciphertext;
}