# FetchContent requires at least cmake-3.11
cmake_minimum_required(VERSION 3.11)
project(hello_test)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)

include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)

# enable test mode
enable_testing()

# add test sources
add_executable(
    hello_test
    hello_test.cc
)
target_link_libraries(
    hello_test
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(hello_test)

# ref: https://google.github.io/googletest/quickstart-cmake.html
# ref: https://google.github.io/googletest/primer.html