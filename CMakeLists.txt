cmake_minimum_required(VERSION 3.13)
project(Cryptography1)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenSSL REQUIRED)

# Find GMP and GMPXX
find_path(GMP_INCLUDE_DIR NAMES gmp.h)
find_library(GMP_LIBRARIES NAMES gmp)
find_path(GMPXX_INCLUDE_DIR NAMES gmpxx.h)
find_library(GMPXX_LIBRARIES NAMES gmpxx)

if(NOT GMP_LIBRARIES OR NOT GMPXX_LIBRARIES)
    message(FATAL_ERROR "GMP or GMPXX not found. Please install them (e.g., 'sudo apt install gmp').")
endif()

file(GLOB_RECURSE Cryptography1_sources
        "${CMAKE_CURRENT_LIST_DIR}/app/main.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/src/*.cpp"
)

add_executable(Cryptography1
        ${Cryptography1_sources}
)

target_link_libraries(Cryptography1 PRIVATE 
    OpenSSL::SSL 
    OpenSSL::Crypto
    ${GMPXX_LIBRARIES}
    ${GMP_LIBRARIES}
)

# Include headers
target_include_directories(Cryptography1 PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/include
        ${GMP_INCLUDE_DIR}
        ${GMPXX_INCLUDE_DIR}
)