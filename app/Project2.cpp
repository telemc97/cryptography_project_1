//
// Created by Tilemahos Mitroudas on 23/12/25.
//

#include "Types.h"
#include "Logger.h"
#include "Math.h"

void exercise1p2() {
    constexpr uint8 bits = 200;

    uint16 attempts = 0;
    bool found = false;
    String candidate_str;

    while (!found) {
        attempts++;
        candidate_str = Math::generateRandomOddNumber(bits);

        Logger::instance().log("Attempt #%i, Checking %s ... ", attempts, candidate_str.c_str());

        if (Math::isPrime(candidate_str)) {
            Logger::instance().log("Prime Found");
            found = true;
        } else {
            Logger::instance().log("Composite");
        }
    }

    Logger::instance().print_separator();
    Logger::instance().log("Result: %s", candidate_str.c_str());
    Logger::instance().log("Attempts: %i", attempts);
}

void exercise3p2() {

    constexpr int32 upper_limit = 2000;

    for (int32 number_1 = 220; number_1 < upper_limit; number_1++) {
        for (int32 number_2 = number_1 + 1; number_2 < upper_limit; number_2++) {
            if (Math::isPairAmicable(number_1, number_2)) {
                Logger::instance().log("%i, %i are amicable numbers", number_1, number_2);
            }
        }
    }
}