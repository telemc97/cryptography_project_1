# Cryptography Project

This project is a C++ implementation of various cryptographic algorithms and mathematical concepts, structured as a series of exercises. It explores topics ranging from polynomial arithmetic and classical ciphers to modern block cipher modes (AES).

## Features & Exercises

The application runs a suite of cryptographic exercises:

*   **Exercise 1: Polynomial Arithmetic**
    *   Demonstrates polynomial division and modular arithmetic.
    *   Implements a custom `Polynomial` class.
*   **Exercise 2: Classical Cryptanalysis**
    *   Performs Kasiski examination and Friedman test to estimate key lengths for polyalphabetic ciphers.
    *   Implements frequency analysis to crack Vigenère ciphers.
*   **Exercise 3: Custom 16-bit Encryption**
    *   Implements a specific linear transformation encryption and its inverse.
*   **Exercise 5: One-Time Pad (OTP)**
    *   Demonstrates perfect secrecy using random key generation and XOR encryption.
*   **Exercise 6: Primitive Polynomials**
    *   Searches for and identifies primitive polynomials over GF(2).
*   **Exercise 9: AES Encryption Modes (ECB vs. CBC)**
    *   Uses OpenSSL to encrypt data using AES in ECB and CBC modes.
    *   Analyzes the avalanche effect by comparing bit differences when the input changes slightly.

## Prerequisites

*   **C++ Compiler:** A compiler supporting C++20 (e.g., GCC, Clang, MSVC).
*   **CMake:** Version 3.10 or higher.
*   **OpenSSL:** The project requires the OpenSSL library (specifically `libssl-dev`).

### Installing Dependencies

**Ubuntu/Debian:**
```bash
sudo apt-get update
sudo apt-get install -y libssl-dev cmake build-essential
```

**macOS:**
```bash
brew install openssl cmake
```

## Project Structure

*   `src/`: Contains source code files (`.cpp`).
*   `include/`: Contains header files (`.h`).
*   `main.cpp`: Entry point of the application.
*   `Jenkinsfile`: CI/CD pipeline configuration.

## CI/CD Pipeline

The project includes a `Jenkinsfile` for continuous integration.

**Pipeline Stages:**
1.  **Install OpenSSL:** Installs necessary dependencies (`libssl-dev`).
2.  **Create Build Folder:** Prepares the build environment. Supports a `CLEAN_BUILD` parameter to wipe the previous build.
3.  **Run CMake:** Configures the build system.
4.  **Build the Project:** Compiles the source code.
