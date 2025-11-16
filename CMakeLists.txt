cmake_minimum_required(VERSION 4.0)
project(Cryptography1)

set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE Cryptography1_sources
        "${CMAKE_CURRENT_LIST_DIR}/main.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/src/*.cpp"
)

add_executable(Cryptography1
        ${Cryptography1_sources}
)

# Include headers
target_include_directories(Cryptography1 PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/include
)