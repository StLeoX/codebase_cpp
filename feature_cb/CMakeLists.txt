project(feature_cb)
message(STATUS "sub project " ${PROJECT_NAME})

add_executable(lambda_demo
    lambda_demo02.cpp)
target_link_libraries(lambda_demo
    pthread)

add_executable(optional_demo
    optional_demo01.cpp)

add_executable(ranges_demo
    ranges_demo01.cpp)

add_executable(regex_demo
    regex_demo.cpp)

add_executable(tuple_demo
    tuple_demo01.cpp)

add_executable(variant_demo
    variant_demo02.cpp)
