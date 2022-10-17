cmake_minimum_required(VERSION 2.8)
project(cpp_code_base)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/cmake-build-debug) # by CLion
include_directories(${CMAKE_SOURCE_DIR}) # include all headers
include_directories(${CMAKE_SOURCE_DIR}/thirdparty/gtest/include)

add_subdirectory(lib_cb) # Libraries
add_subdirectory(stl_cb)
#add_subdirectory(mooon_cb)
add_subdirectory(json_cb)
add_subdirectory(metaprogramming_cb)
add_subdirectory(opt_cb)
add_subdirectory(util_cb)
add_subdirectory(basic_cb)
add_subdirectory(concurrency_cb)
add_subdirectory(feature_cb)
add_subdirectory(common_cb)