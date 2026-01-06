#include "Math.h"
#include <numeric>
#include "Types.h"
#include <vector>
#include <random>
#include <cmath>

#include "Crypto.h"
#include "Utils.h"

#include <gmpxx.h>


uint32 Math::findGCD(const Vector(uint32)& numbers) {
    Vector(BigInt) numbers_to_bigint;
    for (unsigned int number : numbers) {
        numbers_to_bigint.push_back(BigInt(number));
    }
    BigInt gcd = findGCD(numbers_to_bigint);
    return static_cast<uint32>(gcd.get_ui());
}

BigInt Math::findGCD(const Vector(BigInt) &numbers) {
    if (numbers.empty()) {
        return 0;
    }

    BigInt result = numbers[0];
    for (size_t i = 1; i < numbers.size(); ++i) {
        BigInt a = result;
        BigInt b = numbers[i];
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

bool Math::isPrime(const BigInt &number) {
    if (number < 2) return false;
    if (number > 2 && number % 2 == 0) return false;

    // 2. A: (n^2 - 3n + 2) * M1
    const BigInt m1_val(Crypto::calculateM1(number));
    const BigInt term_poly = (number * number) - (3 * number) + 2;
    const BigInt term_a = term_poly * m1_val;

    // 3. B: 8 * M2
    // Call M2 passing the string
    const BigInt m2_val(Crypto::calculateM2(number));
    const BigInt term_b = 8 * m2_val;

    return (term_a - term_b) == 0;
}

bool Math::isPrimeQuick(const BigInt &number) {
    if (number < 2) return false;
    if (number > 2 && number % 2 == 0) return false;

    // Use GMP's probabilistic primality test (Miller-Rabin)
    // 25 repetitions gives a negligible probability of error
    return mpz_probab_prime_p(number.get_mpz_t(), 25) != 0;
}

int32 Math::generateRandomInt(int32 min, int32 max) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<int32> dis(min, max - 1);
    return dis(gen);
}

BigInt Math::generateRandomBigNumber(const uint16 &bits) {
    return generateRandomBigNumber(bits, true, true);
}

BigInt Math::generateRandomBigNumber(const uint16 &bits, const bool &odd, const bool &even) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 1); // 0 or 1

    String binary_string;

    for (int i = 0; i < bits; ++i) {
        // Most Significant Bit (first digit): 1 to have N bits
        if (i == 0) {
            binary_string += '1';
        }
        // Least Significant Bit (last digit): 1 to be odd
        else if (i == bits - 1 && odd != even ) {
            if (even) binary_string += '0';
            if (odd) binary_string += '1';
        }
        else {
            binary_string += (dis(gen) == 1 ? '1' : '0');
        }
    }

    BigInt num_gmp(binary_string, 2);
    return num_gmp;
}

BigInt Math::generateRandomBigEvenNumber(const uint16 &bits) {
    return generateRandomBigNumber(bits, false, true);
}

BigInt Math::generateRandomBigOddNumber(const uint16 &bits) {
    return generateRandomBigNumber(bits, true, false);
}

Vector(int32) Math::findDivisors(const int32 &number) {
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

bool Math::isPairAmicable(const int32 &number_1, const int32 &number_2) {

    Vector(int32) number_1_divisors = findDivisors(number_1);
    Vector(int32) number_2_divisors = findDivisors(number_2);

    int32 sum_number_1_divisors = sum(number_1_divisors);
    int32 sum_number_2_divisors = sum(number_2_divisors);

    return (sum_number_1_divisors == sum_number_2_divisors) && (sum_number_1_divisors == (number_1 + number_2));
}

Vector(BigInt) Math::trialDivision(const BigInt &n_in) {
    BigInt n = n_in;
    Vector(BigInt) factors;

    if (n == 0) {
        factors.push_back(0);
        return factors;
    }
    if (n < 0) {
        factors.push_back(-1);
        n = abs(n);
    }
    if (n == 1) {
        factors.push_back(1);
        return factors;
    }

    // 1. Check for 2
    while (n % 2 == 0) {
        factors.push_back(2);
        n /= 2;
    }

    // 2. Check for odd numbers
    BigInt d = 3;
    BigInt limit = sqrt(n);

    while (d <= limit) {
        if (n % d == 0) {
            factors.push_back(d);
            n /= d;
            limit = sqrt(n);
        } else {
            d += 2;
        }
    }

    // 3. If remaining number > 1
    if (n > 1) {
        factors.push_back(n);
    }

    return factors;
}

BigInt Math::sqrt(const BigInt& n) {
    BigInt res;
    mpz_sqrt(res.get_mpz_t(), n.get_mpz_t());
    return res;
}

float64 Math::sqrt(float64 n) {
    return std::sqrt(n);
}

BigInt Math::pow(const BigInt& base, uint32 exp) {
    BigInt res;
    mpz_pow_ui(res.get_mpz_t(), base.get_mpz_t(), exp);
    return res;
}

float64 Math::pow(float64 base, float64 exp) {
    return std::pow(base, exp);
}

BigInt Math::squareAndMultiply(BigInt base, BigInt exp, const BigInt& mod) {
    BigInt result = 1;
    base %= mod;
    while (exp > 0) {
        if (exp % 2 == 1) result = (result * base) % mod;
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}

int32 Math::squareAndMultiply(int32 base, int32 exp, const int32& mod) {
    return static_cast<int32>(squareAndMultiply(BigInt(base), BigInt(exp), BigInt(mod)).get_si());
}

BigInt Math::modInverse(BigInt a, BigInt m) {
    BigInt m0 = m;
    BigInt r_old = a, r_new = m;
    BigInt s_old = 1, s_new = 0;

    while (r_new != 0) {
        BigInt q = r_old / r_new;

        BigInt temp_r = r_new;
        r_new = r_old - q * r_new;
        r_old = temp_r;

        BigInt temp_s = s_new;
        s_new = s_old - q * s_new;
        s_old = temp_s;
    }

    if (r_old > 1) return 0; // GCD != 1, inverse doesn't exist

    if (s_old < 0) s_old += m0;

    return s_old;
}

int32 Math::modInverse(int32 a, int32 m) {
    BigInt res = modInverse(BigInt(a), BigInt(m));
    return static_cast<int32>(res.get_si());
}

BigInt Math::abs(const BigInt& n) {
    BigInt res;
    mpz_abs(res.get_mpz_t(), n.get_mpz_t());
    return res;
}

float64 Math::abs(float64 n) {
    return std::abs(n);
}

int32 Math::abs(int32 n) {
    return std::abs(n);
}

BigInt Math::extendedGCD(BigInt a, BigInt b, BigInt &x, BigInt &y) {
    if (a == 0) {
        x = 0;
        y = 1;
        return b;
    }
    BigInt x1, y1;
    BigInt d = extendedGCD(b % a, a, x1, y1);
    x = y1 - (b / a) * x1;
    y = x1;
    return d;
}

int32 Math::extendedGCD(int32 a, int32 b, int32 &x, int32 &y) {
    BigInt bx, by;
    BigInt gcd = extendedGCD(BigInt(a), BigInt(b), bx, by);
    x = static_cast<int32>(bx.get_si());
    y = static_cast<int32>(by.get_si());
    return static_cast<int32>(gcd.get_si());
}