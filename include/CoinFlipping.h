//
// Created by Tilemahos Mitroudas on 28/12/25.
//

#ifndef CRYPTOGRAPHY1_COINFLIPPING_H
#define CRYPTOGRAPHY1_COINFLIPPING_H

#include "Types.h"

class CoinFlipping {
public:
    CoinFlipping(const uint16& bits);

    int32 sendN() const;

    void getN(const int32& n);

    int32 sendY();

    int32 getYAndRespond(const int32& y);

    bool getRootAndCheck(const int32& root);

private:
    static int32 generatePrime3Mod4(const uint16& bits);

    int32 p;
    int32 q;
    int32 n;
    int32 y;
    int32 x;

};


#endif //CRYPTOGRAPHY1_COINFLIPPING_H