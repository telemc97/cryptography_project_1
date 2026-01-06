//
// Created by Tilemahos Mitroudas on 28/12/25.
//

#include "CoinFlipping.h"
#include "Math.h"

CoinFlipping::CoinFlipping(const uint16& bits):
p(0),
q(0),
n(0),
y(0),
x(0)
{
    p = generatePrime3Mod4(bits);
    q = generatePrime3Mod4(bits);
    while (p == q) {
        q = generatePrime3Mod4(bits);
    }
    n = p * q;
}

int32 CoinFlipping::sendY() {
    x = Math::generateRandomInt(2, n);
    y = Math::squareAndMultiply(x, 2, n);
    return y;
}

int32 CoinFlipping::getYAndRespond(const int32& y) {
    this->y = y;
    int32 root_p = Math::squareAndMultiply(this->y, (p + 1) / 4, p);
    int32 root_q = Math::squareAndMultiply(this->y, (q + 1) / 4, q);
    int32 a, b;
    Math::extendedGCD(p, q, a, b);
    int32 root_1 = (root_p * b * q + root_q * a * p) % n;
    int32 root_2 = (root_p * b * q - root_q * a * p) % n;
    int32 root_3 = (-root_1) % n;
    int32 root_4 = (-root_2) % n;

    Vector(int32) roots = {root_1, root_2, root_3, root_4};
    int32 random_index = Math::generateRandomInt(0,roots.size());
    return roots[random_index];
}

bool CoinFlipping::getRootAndCheck(const int32 &root) {
    if (root == x || root == (n - x)) {
        return false;
    }
    return true;
}

int32 CoinFlipping::sendN() const {
    return n;
}

void CoinFlipping::getN(const int32 &n) {
    this->n = n;
}

int32 CoinFlipping::generatePrime3Mod4(const uint16& bits) {
    while (true) {
        int32 candidate = Math::generateRandomBigOddNumber(bits).get_ui();
        candidate |= 2;
        if (Math::isPrimeQuick(BigInt(candidate))) {
            return candidate;
        }
    }
}