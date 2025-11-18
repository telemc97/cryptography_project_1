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

float64 Math::average(const Vector(float64)& values) {
    if (values.empty()) {
        return 0.0f; // Return 0 for an empty vector to avoid division by zero
    }

    float64 sum = 0.0f;
    for (float64 value : values) {
        sum += value;
    }
    return sum / values.size();
}