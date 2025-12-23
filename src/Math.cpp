#include "Math.h"
#include <numeric>
#include "Types.h"
#include <vector>
#include <random>

#include "Crypto.h"
#include "Utils.h"

#include <gmpxx.h>

uint32 Math::findGCD(const Vector(uint32) &numbers) {
    if (numbers.empty()) {
        return 0;
    }

    uint32 result = numbers[0];
    for (size_t i = 1; i < numbers.size(); ++i) {
        uint32 a = result;
        uint32 b = numbers[i];
        while (b) {
            a %= b;
            std::swap(a, b);
        }
        result = a;
    }

    return result;
}

int32 Math::mod26(int32 a) {
    int32 result = a % 26;
    if (result < 0) {
        result += 26;
    }
    return result;
}

int32 Math::sum(const Vector(int32)& values) {
    int32 total = 0;
    for (int32 value : values) {
        total += value;
    }
    return total;
}

uint32 Math::sum(const Vector(uint32)& values) {
    uint32 total = 0;
    for (uint32 value : values) {
        total += value;
    }
    return total;
}

float64 Math::sum(const Vector(float64)& values) {
    float64 total = 0.0;
    for (float64 value : values) {
        total += value;
    }
    return total;
}

float64 Math::average(const Vector(float64)& values) {
    if (values.empty()) {
        return 0.0; // Return 0 for an empty vector to avoid division by zero
    }

    return sum(values) / static_cast<float64>(values.size());
}

bool Math::isPrime(const String &number) {

    if (!Utils::isStringNumberValid(number)) {
        return false;
    }

    mpz_class n(number);

    if (n < 2) return false;
    if (n > 2 && n % 2 == 0) return false;

    // 2. Α: (n^2 - 3n + 2) * M1
    const mpz_class m1_val(Crypto::calculateM1(number));
    const mpz_class term_poly = (n * n) - (3 * n) + 2;
    const mpz_class term_a = term_poly * m1_val;

    // 3. Β: 8 * M2
    // Καλούμε την M2 περνώντας το string
    const mpz_class m2_val(Crypto::calculateM2(number));
    const mpz_class term_b = 8 * m2_val;

    return (term_a - term_b) == 0;
}

String Math::generateRandomOddNumber(uint16 bits) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 1); // 0 ή 1

    String binary_string = "";

    for (int i = 0; i < bits; ++i) {
        // Most Significant Bit (first digit): 1 to have N bits
        if (i == 0) {
            binary_string += '1';
        }
        // Least Significant Bit (last digit): 1 to be odd
        else if (i == bits - 1) {
            binary_string += '1';
        }
        else {
            binary_string += (dis(gen) == 1 ? '1' : '0');
        }
    }

    mpz_class num_gmp(binary_string, 2);
    return num_gmp.get_str();
}

Vector(int32) Math::findDivisors(int32 number) {
    Vector(int32) divisors;
    if (number <= 0) {
        return divisors;
    }
    for (int32 i = 1; i <= number; ++i) {
        if (number % i == 0) {
            divisors.push_back(i);
        }
    }
    return divisors;
}

bool Math::isPairAmicable(int32 number_1, int32 number_2) {

    Vector(int32) number_1_divisors = findDivisors(number_1);
    Vector(int32) number_2_divisors = findDivisors(number_2);

    int32 sum_number_1_divisors = sum(number_1_divisors);
    int32 sum_number_2_divisors = sum(number_2_divisors);

    return (sum_number_1_divisors == sum_number_2_divisors) && (sum_number_1_divisors == (number_1 + number_2));
}