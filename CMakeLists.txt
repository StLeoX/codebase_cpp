cmake_minimum_required(VERSION 3.2)
project(codebase_cpp)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/cmake-build-debug) # by CLion
include_directories(${CMAKE_SOURCE_DIR}) # include all headers
include_directories(${CMAKE_SOURCE_DIR}/thirdparty/gtest/include)

#add_subdirectory(mooon_cb)
add_subdirectory(lib_cb)
add_subdirectory(container_cb)
add_subdirectory(design_pattern_cb)
add_subdirectory(opt_cb)
add_subdirectory(util_cb)
add_subdirectory(basic_cb)
add_subdirectory(concurrency_cb)
add_subdirectory(feature_cb)
add_subdirectory(common_cb)