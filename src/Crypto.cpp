#include "Crypto.h"
#include <iostream>
#include <algorithm>
#include "Math.h"
#include "Utils.h"

Crypto::Crypto(String message):
message(message){}

Vector(WordOccurrences) Crypto::findRecurringWords(uint32 minLength) {
    if (this->message.length() < minLength || minLength == 0) {
        return {};
    }

    // 1. Generate all substrings of length minLength
    Vector(String) substrings;
    for (uint32 i = 0; i <= this->message.length() - minLength; ++i) {
        substrings.push_back(this->message.substr(i, minLength));
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

Vector(uint32) Crypto::findDistances(const String& word) const {
    Vector(uint32) distances;
    Vector(uint32) occurrences;

    for (uint32 i = 0; i + word.length() <= this->message.length(); ++i) {
        if (this->message.substr(i, word.length()) == word) {
            occurrences.push_back(i);
        }
    }

    for (uint32 i = 1; i < occurrences.size(); ++i) {
        distances.push_back(occurrences[i] - occurrences[i-1]);
    }

    return distances;
}

Vector(String) Crypto::splitEncryptedMessageReturnRows(uint32 keyLength) const {
    if (keyLength == 0) {
        return {};
    }

    Vector(String) columns = this->splitEncryptedMessageReturnColumns(keyLength);
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

Vector(String) Crypto::splitEncryptedMessageReturnColumns(uint32 keyLength) const {
    Vector(String) columns(keyLength); // Initialize with keyLength empty strings

    if (keyLength == 0) {
        return {}; // Handle invalid keyLength
    }

    for (uint32 i = 0; i < this->message.length(); ++i) {
        columns[i % keyLength] += this->message[i];
    }

    return columns;
}

uint32 Crypto::findKeyLengthKasiski(const uint32 min_word_length) {
    Vector(WordOccurrences) occurrences = this->findRecurringWords(min_word_length);
    if (occurrences.empty()) {
        return 0; // Or handle error appropriately
    }
    Vector(uint32) word_distances = this->findDistances(occurrences[0].word);
    uint32 key_lenght = Math::findGCD(word_distances);
    return key_lenght;
}

char Crypto::findMostFrequentCharInString(const String& text) const {
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

String Crypto::decryptMessageWithKey(const String key) {
    String decrypted_message;
    Vector(String) splitted_message = this->splitEncryptedMessageReturnRows(key.length());
    // Iterate over message columns
    for (Vector(String)::iterator it = splitted_message.begin(); it != splitted_message.end(); ++it) {
        // Iterate over String characters
        for (int i = 0; i < it->length(); i++) {
            const int8 encrypted_char = Utils::convertEnglishCharToInt((*it)[i]);
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

uint32 Crypto::findKeyLengthFriedman(const uint32 max_key_length) {
    uint32  best_key_length = 0;
    float64 english_ic = 0.067;
    float64 min_ic_difference = 1.0;
    String message = this->message;

    for (uint32 key_length = 2; key_length < max_key_length; key_length++) {

        Vector(String) splitted_message_collums = this->splitEncryptedMessageReturnColumns(key_length);

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

String Crypto::getKeyWithFrequencyAnalysis(uint32 key_length) {
    Vector(String) text_collums = this->splitEncryptedMessageReturnColumns(key_length);
    String key;
    for (Vector(String)::iterator it = text_collums.begin(); it != text_collums.end(); ++it) {
        key+=this->findMostFrequentCharInString(*it);
    }
    return key;
}

