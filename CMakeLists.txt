cmake_minimum_required(VERSION 3.13)
project(Cryptography1)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenSSL REQUIRED)

file(GLOB_RECURSE Cryptography1_sources
        "${CMAKE_CURRENT_LIST_DIR}/main.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/src/*.cpp"
)

add_executable(Cryptography1
        ${Cryptography1_sources}
)

target_link_libraries(Cryptography1 PRIVATE OpenSSL::SSL OpenSSL::Crypto)

# Include headers
target_include_directories(Cryptography1 PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/include
)