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
     * @param coeffs A vector of int32 coefficients, from highest degree to lowest.
     */
    Polynomial(uint32 deg, const Vector(int32)& coeffs);

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
    const Vector(int32)& getCoefficients() const;

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

    /**
     * @brief Performs polynomial addition over GF(2).
     * @param a The first polynomial.
     * @param b The second polynomial.
     * @return The sum of the two polynomials over GF(2).
     */
    static Polynomial gf2Add(const Polynomial& a, const Polynomial& b);

    /**
     * @brief Performs polynomial multiplication over GF(2).
     * @param a The first polynomial.
     * @param b The second polynomial.
     * @return The product of the two polynomials over GF(2).
     */
    static Polynomial gf2Multiply(const Polynomial& a, const Polynomial& b);

    /**
     * @brief Performs polynomial modulo over GF(2).
     * @param a The dividend polynomial.
     * @param b The divisor polynomial.
     * @return The remainder of the polynomial division over GF(2).
     */
    static Polynomial gf2Mod(const Polynomial& a, const Polynomial& b);

    /**
     * @brief Checks if the polynomial is irreducible over GF(2).
     * @return True if the polynomial is irreducible, false otherwise.
     */
    boolean gf2IsIrreducible() const;

    /**
     * @brief Checks if the polynomial is primitive over GF(2).
     * @return True if the polynomial is primitive, false otherwise.
     */
    boolean gf2IsPrimitive() const;

private:
    /**
     * @brief Checks if the polynomial's coefficients are valid for GF(2) (i.e., only 0 or 1).
     * @return True if the polynomial is a valid GF(2) polynomial, false otherwise.
     */
    bool gf2IsValid() const;

    /**
     * @brief Performs modular exponentiation for polynomials over GF(2).
     * @param base The base polynomial.
     * @param exp The exponent.
     * @param mod The modulus polynomial.
     * @return The result of (base^exp) mod mod over GF(2).
     */
    static Polynomial gf2Power(const Polynomial& base, uint32 exp, const Polynomial& mod);

    /**
     * @brief The degree of the polynomial.
     * TODO: The degree can be omitted and determined by the coefficients.
     */
    uint32 degree;
    /**
     * @brief A vector storing the coefficients of the polynomial.
     *
     * coefficients[i] represents the coefficient of x^i.
     */
    Vector(int32) coefficients;
};

#endif //CRYPTOGRAPHY1_POLYNOMIAL_H
