project(basic_cb)
message(STATUS "sub project " ${PROJECT_NAME})

add_executable(
    basic_cb
    explicit_ctor.cpp
)