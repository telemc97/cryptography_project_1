#ifndef CRYPTOGRAPHY1_POLYNOMIAL_H
#define CRYPTOGRAPHY1_POLYNOMIAL_H

#include <vector>
#include "Types.h"

/**
 * @brief Represents a polynomial with integer coefficients.
 *
 *
 * The polynomial is represented as:
 * P(x) = c_n * x^n + c_{n-1} * x^{n-1} + ... + c_1 * x + c_0
 * where n is the degree and c_i are the coefficients.
 */
class Polynomial {

public:
    /**
     * @brief Constructs a new Polynomial object.
     * @param deg The degree of the polynomial.
     * @param coeffs A vector of float64 coefficients, from highest degree to lowest.
     */
    Polynomial(uint32 deg, const Vector(float64)& coeffs);

    /**
     * @brief Overloads the addition operator for polynomials.
     * @param other The polynomial to add.
     * @return A new polynomial representing the sum.
     */
    Polynomial operator+(const Polynomial& other) const;

    /**
     * @brief Overloads the subtraction operator for polynomials.
     * @param other The polynomial to subtract.
     * @return A new polynomial representing the difference.
     */
    Polynomial operator-(const Polynomial& other) const;

    /**
     * @brief Overloads the multiplication operator for polynomials.
     * @param other The polynomial to multiply by.
     * @return A new polynomial representing the product.
     */
    Polynomial operator*(const Polynomial& other) const;

    /**
     * @brief Overloads the division operator for polynomials (returns quotient).
     * @param other The polynomial to divide by.
     * @return A new polynomial representing the quotient.
     */
    Polynomial operator/(const Polynomial& other) const;

    /**
     * @brief Overloads the modulo operator for polynomials (returns remainder).
     * @param other The polynomial to divide by.
     * @return A new polynomial representing the remainder.
     */
    Polynomial operator%(const Polynomial& other) const;

    /**
     * @brief Gets the degree of the polynomial.
     * @return The degree of the polynomial.
     */
    uint32 getDegree() const;

    /**
     * @brief Gets the coefficients of the polynomial.
     * @return A const reference to the vector of coefficients.
     */
    const Vector(float64)& getCoefficients() const;

    /**
     * @brief Converts the polynomial to a string representation.
     * @return A string representation of the polynomial.
     */
    String toString() const;

    /**
     * @brief Checks if the polynomial is zero.
     * @return True if the polynomial is zero, false otherwise.
     */
    bool isZero() const;

private:
    /**
     * @brief The degree of the polynomial.
     */
    uint32 degree;
    /**
     * @brief A vector storing the coefficients of the polynomial.
     *
     * coefficients[i] represents the coefficient of x^i.
     */
    std::vector<float64> coefficients;
};

#endif //CRYPTOGRAPHY1_POLYNOMIAL_H
