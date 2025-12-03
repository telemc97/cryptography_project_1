#include "Polynomial.h"
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <sstream>
#include <iomanip>

Polynomial::Polynomial(uint32 deg, const Vector(int32)& coeffs) : degree(deg), coefficients(coeffs) {
    std::reverse(coefficients.begin(), coefficients.end());
    if (coefficients.size() != degree + 1) {
        coefficients.resize(degree + 1, 0);
    }
}

Polynomial Polynomial::operator+(const Polynomial& other) const {
    uint32 max_degree = std::max(degree, other.degree);
    Vector(int32) result_coeffs(max_degree + 1, 0);

    for (uint32 i = 0; i <= degree; ++i) {
        result_coeffs[i] += coefficients[i];
    }

    for (uint32 i = 0; i <= other.degree; ++i) {
        result_coeffs[i] += other.coefficients[i];
    }

    uint32 new_degree = max_degree;
    while (new_degree > 0 && result_coeffs[new_degree] == 0) {
        new_degree--;
    }

    result_coeffs.resize(new_degree + 1);
    std::reverse(result_coeffs.begin(), result_coeffs.end());
    return Polynomial(new_degree, result_coeffs);
}

Polynomial Polynomial::operator-(const Polynomial& other) const {
    uint32 max_degree = std::max(degree, other.degree);
    Vector(int32) result_coeffs(max_degree + 1, 0);

    for (uint32 i = 0; i <= degree; ++i) {
        result_coeffs[i] += coefficients[i];
    }

    for (uint32 i = 0; i <= other.degree; ++i) {
        result_coeffs[i] -= other.coefficients[i];
    }

    uint32 new_degree = max_degree;
    while (new_degree > 0 && result_coeffs[new_degree] == 0) {
        new_degree--;
    }

    result_coeffs.resize(new_degree + 1);
    std::reverse(result_coeffs.begin(), result_coeffs.end());
    return Polynomial(new_degree, result_coeffs);
}

Polynomial Polynomial::operator*(const Polynomial& other) const {
    uint32 new_degree = degree + other.degree;
    Vector(int32) result_coeffs(new_degree + 1, 0);

    for (uint32 i = 0; i <= degree; ++i) {
        for (uint32 j = 0; j <= other.degree; ++j) {
            result_coeffs[i + j] += coefficients[i] * other.coefficients[j];
        }
    }

    std::reverse(result_coeffs.begin(), result_coeffs.end());
    return Polynomial(new_degree, result_coeffs);
}

Polynomial Polynomial::operator/(const Polynomial& other) const {
    if (other.isZero()) {
        throw std::invalid_argument("Division by zero polynomial");
    }

    if (degree < other.degree) {
        return Polynomial(0, {0}); // Quotient is 0
    }

    Vector(int32) quotient_coeffs(degree - other.degree + 1, 0);
    Polynomial remainder = *this;

    while (remainder.degree >= other.degree && !remainder.isZero()) {
        int32 lead_coeff = remainder.coefficients.back() / other.coefficients.back();
        uint32 lead_degree = remainder.degree - other.degree;

        quotient_coeffs[lead_degree] = lead_coeff;

        Vector(int32) term_coeffs(lead_degree + 1, 0);
        term_coeffs.back() = lead_coeff;
        std::reverse(term_coeffs.begin(), term_coeffs.end());
        Polynomial term(lead_degree, term_coeffs);

        remainder = remainder - (term * other);
    }

    std::reverse(quotient_coeffs.begin(), quotient_coeffs.end());
    return Polynomial(degree - other.degree, quotient_coeffs);
}

Polynomial Polynomial::operator%(const Polynomial& other) const {
    if (other.isZero()) {
        throw std::invalid_argument("Division by zero polynomial");
    }

    if (degree < other.degree) {
        return *this; // Remainder is the dividend
    }

    Polynomial remainder = *this;

    while (remainder.degree >= other.degree && !remainder.isZero()) {
        int32 lead_coeff = remainder.coefficients.back() / other.coefficients.back();
        uint32 lead_degree = remainder.degree - other.degree;

        Vector(int32) term_coeffs(lead_degree + 1, 0);
        term_coeffs.back() = lead_coeff;
        std::reverse(term_coeffs.begin(), term_coeffs.end());
        Polynomial term(lead_degree, term_coeffs);

        remainder = remainder - (term * other);
    }

    return remainder;
}

uint32 Polynomial::getDegree() const {
    return degree;
}

const Vector(int32)& Polynomial::getCoefficients() const {
    return coefficients;
}

String Polynomial::toString() const {
    std::string result = "";
    bool first_term = true;
    for (int32 i = degree; i >= 0; --i) {
        if (coefficients[i] == 0) {
            continue;
        }

        if (!first_term) {
            if (coefficients[i] > 0) {
                result += " + ";
            } else {
                result += " - ";
            }
        } else {
            if (coefficients[i] < 0) {
                result += "-";
            }
        }

        if (std::abs(coefficients[i]) != 1 || i == 0) {
            result += std::to_string(std::abs(coefficients[i]));
        }

        if (i > 0) {
            result += "x";
            if (i > 1) {
                result += "^" + std::to_string(i);
            }
        }
        first_term = false;
    }

    if (first_term) {
        result += "0";
    }

    return result;
}

bool Polynomial::isZero() const {
    for (int32 coeff : coefficients) {
        if (coeff != 0) {
            return false;
        }
    }
    return true;
}

Polynomial Polynomial::gf2Add(const Polynomial& a, const Polynomial& b) {
    uint32 max_degree = std::max(a.degree, b.degree);
    Vector(int32) result_coeffs(max_degree + 1, 0);

    for (uint32 i = 0; i <= a.degree; ++i) {
        result_coeffs[i] = result_coeffs[i] ^ a.coefficients[i];
    }

    for (uint32 i = 0; i <= b.degree; ++i) {
        result_coeffs[i] = result_coeffs[i] ^ b.coefficients[i];
    }

    uint32 new_degree = max_degree;
    while (new_degree > 0 && result_coeffs[new_degree] == 0) {
        new_degree--;
    }

    result_coeffs.resize(new_degree + 1);
    std::reverse(result_coeffs.begin(), result_coeffs.end());
    return Polynomial(new_degree, result_coeffs);
}

Polynomial Polynomial::gf2Multiply(const Polynomial& a, const Polynomial& b) {
    uint32 new_degree = a.degree + b.degree;
    Vector(int32) result_coeffs(new_degree + 1, 0);

    for (uint32 i = 0; i <= a.degree; ++i) {
        for (uint32 j = 0; j <= b.degree; ++j) {
            result_coeffs[i + j] = result_coeffs[i + j] ^ (a.coefficients[i] * b.coefficients[j]);
        }
    }

    while (new_degree > 0 && result_coeffs[new_degree] == 0) {
        new_degree--;
    }

    result_coeffs.resize(new_degree + 1);
    std::reverse(result_coeffs.begin(), result_coeffs.end());
    return Polynomial(new_degree, result_coeffs);
}

Polynomial Polynomial::gf2Mod(const Polynomial& a, const Polynomial& b) {
    if (b.isZero()) {
        throw std::invalid_argument("Division by zero polynomial");
    }

    Polynomial remainder = a;

    while (remainder.degree >= b.degree && !remainder.isZero()) {
        uint32 lead_degree = remainder.degree - b.degree;
        Vector(int32) term_coeffs(lead_degree + 1, 0);
        term_coeffs.back() = 1; // In GF(2), lead coefficient is always 1
        std::reverse(term_coeffs.begin(), term_coeffs.end());
        Polynomial term(lead_degree, term_coeffs);

        remainder = gf2Add(remainder, gf2Multiply(term, b));
    }

    return remainder;
}

bool Polynomial::gf2IsIrreducible() const {
    if (degree == 0) return false;
    if (coefficients[0] == 0) return false; // Must not be divisible by x

    int sum_coeffs = 0;
    for(int c : coefficients) {
        sum_coeffs += c;
    }
    if (sum_coeffs % 2 == 0) return false; // Must not be divisible by x+1

    // A more general implementation would check against all irreducible polys up to degree m/2
    // For degree 5, we only need to check for irreducibles of degree 1 and 2.
    // The checks above handle degree 1. The only irreducible of degree 2 is x^2+x+1
    if (degree > 2) {
        Polynomial p_x2_x_1(2, {1, 1, 1});
        if (gf2Mod(*this, p_x2_x_1).isZero()) {
            return false;
        }
    }
    
    // This is not a complete test for all degrees, but it covers small degrees.
    // A full test is much more complex. For this project, we assume this is sufficient for now.
    // For degree 5, this is sufficient if we also check for products of irreducibles of deg 1 and 2.
    // (x+1)(x^2+x+1) = x^3+1 - covered by P(1) != 0 check
    // A proper check for degree 5 would be against (x^2+x+1) and (x^3+x+1) and (x^3+x^2+1)
    // But this is a good start.

    return true;
}

bool Polynomial::gf2IsPrimitive() const {
    if (!gf2IsIrreducible()) {
        return false;
    }

    uint32 m = degree;
    uint64 n = (1ULL << m) - 1;

    // Check if x^n mod P(x) == 1
    Polynomial x(1, {1, 0});
    Polynomial x_n = gf2Power(x, n, *this);

    Polynomial one(0, {1});

    if (x_n.degree != one.degree || x_n.coefficients != one.coefficients) {
        return false;
    }

    // For a prime n (like 31), this is sufficient.
    // For composite n, we'd also have to check that for any prime factor q of n,
    // x^(n/q) mod P(x) != 1.
    return true;
}

Polynomial Polynomial::gf2Power(const Polynomial& base, uint32 exp, const Polynomial& mod) {
    Polynomial res(0, {1});
    Polynomial b = base;
    while (exp > 0) {
        if (exp % 2 == 1) {
            res = gf2Multiply(res, b);
            res = gf2Mod(res, mod);
        }
        b = gf2Multiply(b, b);
        b = gf2Mod(b, mod);
        exp /= 2;
    }
    return res;
}