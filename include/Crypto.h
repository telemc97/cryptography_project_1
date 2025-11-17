#ifndef CRYPTOGRAPHY1_CRYPTO_H
#define CRYPTOGRAPHY1_CRYPTO_H

#include "Types.h"

struct WordOccurrences {
    uint32 count;
    String word;
};

class Crypto {
public:
    Crypto(String message);
    Vector(WordOccurrences) findRecurringWords(uint32 minLength);
    Vector(uint32) findDistances(const String& word) const;
    int32 findKeyLengthKasiski();
    Vector(String) splitEncryptedMessageToColumns(uint32 keyLength) const;
    String findMostFrequentChars(const Vector(String)& columns) const;
    String decryptMessageWithKey(String key);
private:
    String message;
};

#endif //CRYPTOGRAPHY1_CRYPTO_H

