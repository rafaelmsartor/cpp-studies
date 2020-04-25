cmake_minimum_required(VERSION 3.14)
project(lox)

set(CMAKE_CXX_STANDARD 17)

include_directories( ${CMAKE_SOURCE_DIR}/include )

add_library( lox_lib STATIC
        src/Interpreter.cpp
        src/Scanner.cpp
        src/Expressions.cpp
        src/Parser.cpp
)

# Genereate the interpreter executable

add_executable(lox
        src/main.cpp
)

target_link_libraries( lox lox_lib )


# Generate the test binaries

add_executable( lox_tests
	tests/token_type_test.cpp
    tests/scanner_test.cpp
)

target_link_libraries( lox_tests lox_lib)