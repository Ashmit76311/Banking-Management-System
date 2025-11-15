cmake_minimum_required(VERSION 3.14)
project(BankingSystem LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# core library from your account implementation
add_library(banklib STATIC account.cpp)

# main executable (optional)
add_executable(bank_system bank_system.cpp)
target_link_libraries(bank_system PRIVATE banklib)

# ---------- GoogleTest via FetchContent ----------
add_subdirectory(${CMAKE_SOURCE_DIR}/extern/googletest EXCLUDE_FROM_ALL)
enable_testing()

# Point to the actual test source file in your repo (assets/tests)
set(TEST_SRC ${CMAKE_SOURCE_DIR}/assets/tests/test_account.cpp)

# Create the test executable and ensure it can find project headers
add_executable(unit_tests ${TEST_SRC})
target_include_directories(unit_tests PRIVATE ${CMAKE_SOURCE_DIR})
target_link_libraries(unit_tests PRIVATE GTest::gtest_main banklib)

# Register the tests with CTest
add_test(NAME unit_tests COMMAND unit_tests)


