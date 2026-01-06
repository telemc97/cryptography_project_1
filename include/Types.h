//
// Created by Tilemahos Mitroudas on 15/11/25.
//

#ifndef CRYPTOGRAPHY1_DATATYPES_H
#define CRYPTOGRAPHY1_DATATYPES_H

#include <array>
#include <vector>
#include <string>
#include <map>
#include <cstddef>
#include <gmpxx.h>

#define int8   signed char
#define int16  short
#define int32  int
#define int64  long long
#define int128 __int128

// Unsigned integer types
#define uint8   unsigned char
#define uint16  unsigned short
#define uint32  unsigned int
#define uint64  unsigned long long
#define uint128 unsigned __int128

// Large Integer (Arbitrary Precision)
#define BigInt mpz_class

// Floating point

// Floating point
#define float32  float
#define float64  double

// Boolean (C++ already has bool, but sometimes for C interop)
//#define boolean  unsigned char

#define wide_char  wchar_t

// Macros for standard types
#define Array(type, size)         std::array<type, size>
#define Vector(type)              std::vector<type>
#define String                    std::string
#define Map(keyType, valueType)   std::map<keyType, valueType>

#endif //CRYPTOGRAPHY1_DATATYPES_H