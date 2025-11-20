#include "Crypto.h"
#include <iostream>
#include <algorithm>
#include "Math.h"
#include "Utils.h"

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
    if (columns.empty()) {
        return {};
    }

    // Determine the number of rows, which is the length of the longest column
    size_t num_rows = 0;
    for (const auto& col : columns) {
        if (col.length() > num_rows) {
            num_rows = col.length();
        }
    }

    Vector(String) rows(num_rows);
    for (size_t i = 0; i < num_rows; ++i) {
        for (size_t j = 0; j < keyLength; ++j) {
            if (i < columns[j].length()) {
                rows[i] += columns[j][i];
            }
        }
    }

    return rows;
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

String Crypto::decryptMessageWithKey(const String &message, const String key) {
    String decrypted_message;
    Vector(String) splitted_message = splitEncryptedMessageReturnRows(message, key.length());
    // Iterate over message columns
    for (auto &message_rows : splitted_message) {
        // Iterate over String characters
        for (int i = 0; i < message_rows.length(); i++) {
            const int8 encrypted_char = Utils::convertEnglishCharToInt(message_rows[i]);
            const int8 key_char = Utils::convertEnglishCharToInt(key[i]);
            const char decrypted_char = Utils::convertIntToEnglishChar(Math::mod26(encrypted_char-key_char));
            decrypted_message+=decrypted_char;
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
    float64 english_ic = 0.067;
    float64 min_ic_difference = 1.0;

    for (uint32 key_length = 2; key_length < max_key_length; key_length++) {

        Vector(String) splitted_message_collums = splitEncryptedMessageReturnColumns(message, key_length);

        Vector(float64) coincidence_indices;
        for (const String& column : splitted_message_collums) {
            coincidence_indices.push_back(calculateIC(column));
        }

        if (!coincidence_indices.empty()) {
            float64 average_ic = Math::average(coincidence_indices);
            float64 ic_differrence = std::abs(average_ic - english_ic);

            if (ic_differrence < min_ic_difference) {
                min_ic_difference = ic_differrence;
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
    Vector(String) text_collums = splitEncryptedMessageReturnColumns(message, key_length);
    String key;
    for (auto &text_collum : text_collums) {
        key+=findMostFrequentCharInString(text_collum);
    }
    return key;
}

uint16 Crypto::decrypt(const uint16 encrypted_msg) {
    // m = c ^ (c << 6) ^ (c << 10) ^ (c << 12)
    return encrypted_msg ^ (static_cast<uint16>(encrypted_msg << 6))
                         ^ (static_cast<uint16>(encrypted_msg << 10))
                         ^ (static_cast<uint16>(encrypted_msg << 12));
}

uint16 Crypto::encrypt(const uint16 decrypted_msg) {
    return decrypted_msg ^ (static_cast<uint16>(decrypted_msg << 6)) ^ (static_cast<uint16>(decrypted_msg << 10));
}
