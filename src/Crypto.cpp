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

Vector(String) Crypto::splitEncryptedMessageToColumns(uint32 keyLength) const {
    Vector(String) blocks;

    if (keyLength == 0) {
        return {}; // Handle invalid keyLength
    }

    for (uint32 i = 0; i < this->message.length(); i += keyLength) {
        blocks.push_back(this->message.substr(i, keyLength));
    }

    return blocks;
}

// Vector(String) Crypto::splitEncryptedMessageToColumns(uint32 keyLength) const {
//     Vector(String) columns(keyLength); // Initialize with keyLength empty strings
//
//     if (keyLength == 0) {
//         return {}; // Handle invalid keyLength
//     }
//
//     for (uint32 i = 0; i < this->message.length(); ++i) {
//         columns[i % keyLength] += this->message[i];
//     }
//
//     return columns;
// }

String Crypto::findMostFrequentChars(const Vector(String)& blocks) const {
    if (blocks.empty() || blocks[0].empty()) {
        return "";
    }

    // Determine the number of positions to check (length of the blocks)
    size_t numPositions = blocks[0].length();
    String mostFrequentChars;

    // Iterate through each character position (column)
    for (size_t pos = 0; pos < numPositions; ++pos) {
        Map(char, int) counts;

        // Gather all characters at the current position from all blocks
        for (const auto& block : blocks) {
            if (pos < block.length()) { // Safety check for uneven blocks
                counts[block[pos]]++;
            }
        }

        // Find the most frequent character for the current position
        char mostFrequentChar = ' ';
        int maxCount = 0;
        if (!counts.empty()) {
            for (const auto& pair : counts) {
                if (pair.second > maxCount) {
                    maxCount = pair.second;
                    mostFrequentChar = pair.first;
                }
            }
            mostFrequentChars += mostFrequentChar;
        }
    }

    return mostFrequentChars;
}

int32 Crypto::findKeyLengthKasiski() {
    int8 min_word_lenght = 4;
    Vector(WordOccurrences) occurrences = this->findRecurringWords(min_word_lenght);
    Vector(uint32) word_distances = this->findDistances(occurrences[0].word);
    int32 key_lenght = Math::findGCD(word_distances);
    return key_lenght;
}

String Crypto::decryptMessageWithKey(const String key) {
    String decrypted_message;
    Vector(String) splitteg_message = this->splitEncryptedMessageToColumns(key.length());
    Vector(String)::iterator it;
    // Iterate over message collumns
    for (it = splitteg_message.begin(); it != splitteg_message.end(); ++it) {
        // Iterate over String characters
        for (int i = 0; i < it->length(); i++) {
            int8 encrypted_char = Utils::convertEnglishCharToInt((*it)[i]);
            int8 key_char = Utils::convertEnglishCharToInt(key[i]);
            char dectypted_char = Utils::convertIntToEnglishChar(Math::mod26(encrypted_char-key_char));
            decrypted_message+=dectypted_char;
        }
    }
    return decrypted_message;
}