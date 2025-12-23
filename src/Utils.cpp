#include "Utils.h"
#include <string>
#include <algorithm>
#include <cctype>

int8 Utils::convertGreekCharToInt(wide_char character) {
    switch (character) {
        case L'Α': case L'α': return 1;
        case L'Β': case L'β': return 2;
        case L'Γ': case L'γ': return 3;
        case L'Δ': case L'δ': return 4;
        case L'Ε': case L'ε': return 5;
        case L'Ζ': case L'ζ': return 6;
        case L'Η': case L'η': return 7;
        case L'Θ': case L'θ': return 8;
        case L'Ι': case L'ι': return 9;
        case L'Κ': case L'κ': return 10;
        case L'Λ': case L'λ': return 11;
        case L'Μ': case L'μ': return 12;
        case L'Ν': case L'ν': return 13;
        case L'Ξ': case L'ξ': return 14;
        case L'Ο': case L'ο': return 15;
        case L'Π': case L'π': return 16;
        case L'Ρ': case L'ρ': return 17;
        case L'Σ': case L'σ': case L'ς': return 18;
        case L'Τ': case L'τ': return 19;
        case L'Υ': case L'υ': return 20;
        case L'Φ': case L'φ': return 21;
        case L'Χ': case L'χ': return 22;
        case L'Ψ': case L'ψ': return 23;
        case L'Ω': case L'ω': return 24;
        default: return 0; // Not a letter
    }
}

wide_char Utils::convertIntToGreekChar(int integer) {
    switch (integer) {
        case 0: case 24: return L'ω';
        case 1: return L'α';
        case 2: return L'β';
        case 3: return L'γ';
        case 4: return L'δ';
        case 5: return L'ε';
        case 6: return L'ζ';
        case 7: return L'η';
        case 8: return L'θ';
        case 9: return L'ι';
        case 10: return L'κ';
        case 11: return L'λ';
        case 12: return L'μ';
        case 13: return L'ν';
        case 14: return L'ξ';
        case 15: return L'ο';
        case 16: return L'π';
        case 17: return L'ρ';
        case 18: return L'σ';
        case 19: return L'τ';
        case 20: return L'υ';
        case 21: return L'φ';
        case 22: return L'χ';
        case 23: return L'ψ';
        default: return L' '; // Return a space for out-of-range integers
    }
}

int8 Utils::convertCharToInt(char c, const String& charset) {
    c = static_cast<char>(std::tolower(c));
    size_t pos = charset.find(c);
    if (pos != String::npos) {
        return static_cast<int8>(pos);
    }
    return -1;
}

char Utils::convertIntToChar(uint8 i, const String& charset) {
    if (i < charset.length()) {
        return charset[i];
    }
    return ' ';
}


Vector(uint8) Utils::getDigits(const uint32 &number) {
    if (number == 0) {
        return {0};
    }

    Vector(uint8) digits;
    uint32 num = number;
    while (num > 0) {
        digits.push_back(num % 10);
        num /= 10;
    }
    std::reverse(digits.begin(), digits.end());
    return digits;
}

Vector(String) Utils::transposeVectorString(const Vector(String)& string_vector) {
    if (string_vector.empty()) {
        return {};
    }

    Vector(String) transposed_vector(string_vector[0].length());
    for (size_t i = 0; i < string_vector.size(); ++i) {
        for (size_t j = 0; j < string_vector[i].length(); ++j) {
            transposed_vector[j] += string_vector[i][j];
        }
    }

    return transposed_vector;
}

#include <bitset>

String Utils::flatten(const Vector(String)& string_vector) {
    String flattened_string;
    for (const auto& s : string_vector) {
        flattened_string += s;
    }
    return flattened_string;
}

String Utils::toBitString(const String& value) {
    String bit_string;
    bit_string.reserve(value.length() * 8);
    for (char c : value) {
        bit_string += std::bitset<8>(c).to_string();
    }
    return bit_string;
}

#include <cstddef>
#include <openssl/rand.h>
#include <stdexcept>

Vector(int32) Utils::intToBits(const int32 &value) {
    const int32 num_bits = sizeof(int32) * 8;
    std::bitset<num_bits> bits(value);

    Vector(int32) bit_vector;
    bit_vector.reserve(num_bits);

    for (int32 i = num_bits - 1; i >= 0; --i) {
        bit_vector.push_back(bits[i]);
    }
    
    return bit_vector;
}

#include <random>

String Utils::generateRandomString(size_t length, const String& charset) {
    if (charset.empty()) {
        return "";
    }

    String random_string;
    random_string.reserve(length);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, charset.length() - 1);

    for (size_t i = 0; i < length; ++i) {
        random_string += charset[distrib(gen)];
    }

    return random_string;
}

bool Utils::isStringNumberValid(const std::string &number) {
    if (number.empty()) return false;

    for (const char c : number) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}

