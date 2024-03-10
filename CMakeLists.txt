cmake_minimum_required(VERSION 2.8)

project(AdvAuction)

set(CMAKE_CXX_STANDARD 20)

add_executable(AdvAuction 
    src/main.cpp 
    src/AdvAuction.h 
    src/AdvAuction.cpp
)

enable_testing()

add_executable(ci_tests
    tests/tests.h
    tests/tests.cpp 
    tests/test_runner.h
    src/AdvAuction.h 
    src/AdvAuction.cpp
)

include(GoogleTest)
gtest_discover_tests(ci_tests)
