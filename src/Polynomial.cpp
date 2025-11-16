#include "Polynomial.h"
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <sstream>
#include <iomanip>

Polynomial::Polynomial(uint32 deg, const Vector(float64)& coeffs) : degree(deg), coefficients(coeffs) {
    std::reverse(coefficients.begin(), coefficients.end());
    if (coefficients.size() != degree + 1) {
        coefficients.resize(degree + 1, 0.0);
    }
}

Polynomial Polynomial::operator+(const Polynomial& other) const {
    uint32 max_degree = std::max(degree, other.degree);
    Vector(float64) result_coeffs(max_degree + 1, 0.0);

    for (uint32 i = 0; i <= degree; ++i) {
        result_coeffs[i] += coefficients[i];
    }

    for (uint32 i = 0; i <= other.degree; ++i) {
        result_coeffs[i] += other.coefficients[i];
    }

    uint32 new_degree = max_degree;
    while (new_degree > 0 && result_coeffs[new_degree] == 0.0) {
        new_degree--;
    }

    result_coeffs.resize(new_degree + 1);
    std::reverse(result_coeffs.begin(), result_coeffs.end());
    return Polynomial(new_degree, result_coeffs);
}

Polynomial Polynomial::operator-(const Polynomial& other) const {
    uint32 max_degree = std::max(degree, other.degree);
    Vector(float64) result_coeffs(max_degree + 1, 0.0);

    for (uint32 i = 0; i <= degree; ++i) {
        result_coeffs[i] += coefficients[i];
    }

    for (uint32 i = 0; i <= other.degree; ++i) {
        result_coeffs[i] -= other.coefficients[i];
    }

    uint32 new_degree = max_degree;
    while (new_degree > 0 && result_coeffs[new_degree] == 0.0) {
        new_degree--;
    }

    result_coeffs.resize(new_degree + 1);
    std::reverse(result_coeffs.begin(), result_coeffs.end());
    return Polynomial(new_degree, result_coeffs);
}

Polynomial Polynomial::operator*(const Polynomial& other) const {
    uint32 new_degree = degree + other.degree;
    Vector(float64) result_coeffs(new_degree + 1, 0.0);

    for (uint32 i = 0; i <= degree; ++i) {
        for (uint32 j = 0; j <= other.degree; ++j) {
            result_coeffs[i + j] += coefficients[i] * other.coefficients[j];
        }
    }

    std::reverse(result_coeffs.begin(), result_coeffs.end());
    return Polynomial(new_degree, result_coeffs);
}

Polynomial Polynomial::operator/(const Polynomial& other) const {
    if (other.degree == 0 && other.coefficients[0] == 0.0) {
        throw std::invalid_argument("Division by zero polynomial");
    }

    if (degree < other.degree) {
        return Polynomial(0, {0.0}); // Quotient is 0
    }

    Vector(float64) quotient_coeffs(degree - other.degree + 1, 0.0);
    Polynomial remainder = *this;

    while (remainder.degree >= other.degree && !remainder.isZero()) {
        float64 lead_coeff = remainder.coefficients.back() / other.coefficients.back();
        uint32 lead_degree = remainder.degree - other.degree;

        quotient_coeffs[lead_degree] = lead_coeff;

        Vector(float64) term_coeffs(lead_degree + 1, 0.0);
        term_coeffs.back() = lead_coeff;
        std::reverse(term_coeffs.begin(), term_coeffs.end());
        Polynomial term(lead_degree, term_coeffs);

        remainder = remainder - (term * other);
    }

    std::reverse(quotient_coeffs.begin(), quotient_coeffs.end());
    return Polynomial(degree - other.degree, quotient_coeffs);
}

Polynomial Polynomial::operator%(const Polynomial& other) const {
    if (other.degree == 0 && other.coefficients[0] == 0.0) {
        throw std::invalid_argument("Division by zero polynomial");
    }

    if (degree < other.degree) {
        return *this; // Remainder is the dividend
    }

    Polynomial remainder = *this;

    while (remainder.degree >= other.degree && !remainder.isZero()) {
        float64 lead_coeff = remainder.coefficients.back() / other.coefficients.back();
        uint32 lead_degree = remainder.degree - other.degree;

        Vector(float64) term_coeffs(lead_degree + 1, 0.0);
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

const Vector(float64)& Polynomial::getCoefficients() const {
    return coefficients;
}

String Polynomial::toString() const {
    std::string result = "";
    bool first_term = true;
    for (int32 i = degree; i >= 0; --i) {
        if (coefficients[i] == 0.0) {
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

        if (std::abs(coefficients[i]) != 1.0 || i == 0) {
            std::stringstream ss;
            float64 current_coeff = std::abs(coefficients[i]);
            if (current_coeff == floor(current_coeff)) {
                ss << static_cast<int64>(current_coeff);
            } else {
                ss << std::fixed << std::setprecision(3) << current_coeff;
                std::string s = ss.str();
                s.erase(s.find_last_not_of('0') + 1, std::string::npos);
                if (s.back() == '.') {
                    s.pop_back();
                }
                ss.str(""); // Clear the stringstream
                ss << s;    // Put the formatted string back
            }
            result += ss.str();
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
    for (float64 coeff : coefficients) {
        if (coeff != 0.0) {
            return false;
        }
    }
    return true;
}