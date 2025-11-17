#include "Math.h"
#include <numeric>
#include "Types.h"
#include <vector>

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

int Math::mod26(int a) {
    int result = a % 26;
    if (result < 0) {
        result += 26;
    }
    return result;
}