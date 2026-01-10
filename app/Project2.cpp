//
// Created by Tilemahos Mitroudas on 23/12/25.
//

#include "CoinFlipping.h"
#include "Crypto.h"
#include "Types.h"
#include "Logger.h"
#include "Math.h"
#include "Utils.h"
#include <chrono>

void exercise1p2() {
    constexpr uint8 bits = 200;

    uint16 attempts = 0;
    bool found = false;
    BigInt candidate_number;

    while (!found) {
        attempts++;
        candidate_number = Math::generateRandomBigNumber(bits);

        Logger::instance().log("Attempt #%i, Checking %s ... ", attempts, candidate_number.get_str().c_str());

        if (Math::isPrimeMacMahon(candidate_number)) {
            Logger::instance().log("Prime Found");
            found = true;
        } else {
            Logger::instance().log("Composite");
        }
    }

    Logger::instance().print_separator();
    Logger::instance().log("Result: %s", candidate_number.get_str().c_str());
    Logger::instance().log("Attempts: %i", attempts);
}

void exercise3p2() {

    constexpr int32 upper_limit = 10000;

    for (int32 number_1 = 220; number_1 < upper_limit; number_1++) {
        for (int32 number_2 = number_1 + 1; number_2 < upper_limit; number_2++) {
            if (Math::isPairAmicable(number_1, number_2)) {
                Logger::instance().log("%i, %i are amicable numbers", number_1, number_2);
            }
        }
    }
}

void exercise8p2() {
    auto start = std::chrono::high_resolution_clock::now();

    BigInt k = 835335;
    int32 exponent = 39014;

    BigInt common_term = k * Math::pow(BigInt(2), exponent);

    BigInt num1 = common_term - 1;
    BigInt num2 = common_term + 1;

    if (Math::squareAndMultiply(2, num1 - 1, num1) == 1) {
        Logger::instance().log("Fermat test passed for N1: %s Its prime", num1.get_str().c_str());
    } else {
        Logger::instance().log("Its composite");
    }

    if (Math::squareAndMultiply(2, num2 - 1, num2) == 1) {
        Logger::instance().log("Fermat test passed for N2: %s Its prime", num2.get_str().c_str());
    } else {
        Logger::instance().log("Its composite");
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    Logger::instance().log("Execution time: %lld ms", static_cast<long long>(duration.count()));
}


void exercise9p2() {
    BigInt number_1("4611686018427387904");
    BigInt number_2("-1");
    BigInt number_3("5070602400912917605986812821503");

    auto print_factors = [](const BigInt& num, const Vector(BigInt)& factors) {
        String result;
        for (size_t i = 0; i < factors.size(); ++i) {
            result += factors[i].get_str();
            if (i < factors.size() - 1) {
                result += " x ";
            }
        }
        Logger::instance().log("factorization of %s results in %s", num.get_str().c_str(), result.c_str());
    };

    Vector(BigInt) result_1 = Math::trialDivision(number_1);
    print_factors(number_1, result_1);

    Vector(BigInt) result_2 = Math::trialDivision(number_2);
    print_factors(number_2, result_2);

    Vector(BigInt) result_3 = Math::trialDivision(number_3);
    print_factors(number_3, result_3);
}

void exercise10p2() {
    BigInt number(Math::generateRandomBigNumber(100));

    Logger::instance().log("Factor search for number %s", number.get_str().c_str());

    auto f = [](const BigInt &x, const BigInt &n) -> BigInt {
        return (x * x  + 1) % n;
    };

    BigInt x = 2;
    BigInt y = 2;
    BigInt d = 1;

    while (true) {

        x = f(x, number);
        y = f(f(y, number), number);
        d = Math::findGCD({Math::abs(x - y), number});
        if (d > 1 && d < number) {
            Logger::instance().log("Factor found %s", d.get_str().c_str());
            BigInt second_factor = number / d;
            Logger::instance().log("Other factor is %s", second_factor.get_str().c_str());
            return;
        }

        if (d == number) {
            Logger::instance().log("Failed to find factor");
            return;
        }
    }
}

void exercise11p2() {
    const int32 N = 11413;
    const int32 e = 19;
    const int32 c = 3215;

    Vector(BigInt) factors = Math::trialDivision(BigInt(N));

    const int32 p = static_cast<int32>(factors[0].get_si());
    const int32 q = static_cast<int32>(factors[1].get_si());

    const int32 phi_N = (p - 1) * (q - 1);

    const int32 d = Math::modInverse(e, phi_N);
    Logger::instance().log("Private key: %i", d);

    const int32 m = Math::squareAndMultiply(c, d, N);
    Logger::instance().log("Decrypted message: %i", m);
}

void exercise12p2() {
    constexpr uint16 bits = 2;
    CoinFlipping bob = CoinFlipping(bits);
    CoinFlipping alice = CoinFlipping(bits);

    const int32 alice_n = alice.sendN();
    bob.getN(alice_n);
    const int32 bob_y = bob.sendY();
    int32 alice_root = alice.getYAndRespond(bob_y);
    bool result = bob.getRootAndCheck(alice_root);
    if (result) {
        Logger::instance().log("Bob Won");
    } else {
        Logger::instance().log("Alice Won");
    }
}

void exercise13p2() {
    const BigInt N = BigInt(194749497518847283);
    const BigInt e = BigInt(50736902528669041);

    BigInt found_private_key;
    BigInt found_q;
    BigInt found_p;

    const bool wiener_attack_outcome = Crypto::wienerAttack(N, e, found_private_key, found_q, found_p);
    Vector(String) cyphertext = {"47406263192693509","51065178201172223","30260565235128704","82385963334404268",
                                      "8169156663927929","47406263192693509","178275977336696442","134434295894803806",
                                      "112111571835512307","119391151761050882","30260565235128704","82385963334404268",
                                      "134434295894803806","47406263192693509","45815320972560202","174632229312041248",
                                      "30260565235128704","47406263192693509","119391151761050882","57208077766585306",
                                      "134434295894803806","47406263192693509","119391151761050882","47406263192693509",
                                      "112111571835512307","52882851026072507","119391151761050882","57208077766585306",
                                      "119391151761050882","112111571835512307","8169156663927929","134434295894803806",
                                      "57208077766585306","47406263192693509","185582105275050932","174632229312041248",
                                      "134434295894803806","82385963334404268","172565386393443624","106356501893546401",
                                      "8169156663927929","47406263192693509","10361059720610816","134434295894803806",
                                      "119391151761050882","172565386393443624","47406263192693509","8169156663927929",
                                      "52882851026072507","119391151761050882","8169156663927929","47406263192693509",
                                      "45815320972560202","174632229312041248","30260565235128704","47406263192693509",
                                      "52882851026072507","119391151761050882","111523408212481879","134434295894803806",
                                      "47406263192693509","112111571835512307","52882851026072507","119391151761050882",
                                      "57208077766585306","119391151761050882","112111571835512307","8169156663927929",
                                      "134434295894803806","57208077766585306"};
    String decrypted_text;

    if (wiener_attack_outcome) {
        Logger::instance().log("Wiener Attack succesfull");
        Logger::instance().log("Found q: %s", found_q.get_str().c_str());
        Logger::instance().log("Found p: %s", found_p.get_str().c_str());
        Logger::instance().log("Private key: %s", found_private_key.get_str().c_str());

        for (const String& c_str : cyphertext) {
            BigInt character = BigInt(c_str);
            BigInt decrypted_character_number = Math::squareAndMultiply(character, found_private_key, N);
            char decrypted_character_char = static_cast<char>(decrypted_character_number.get_ui());
            decrypted_text.push_back(decrypted_character_char);
        }
        Logger::instance().log("Decrypted Text:");
        Logger::instance().log(decrypted_text);

    } else {
        Logger::instance().log("Wiener Attack unsuccesfull");
    }
}