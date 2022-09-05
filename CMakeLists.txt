cmake_minimum_required(VERSION 2.8)
project(cpp_code_base)

# 常用的第三方库
set(
    THIRDPART_LIB
    libgongyi_base.a
    libmooon.a
    libr3c.a libhiredis.a
    libcgicc.a libcurl.a libcares.a libidn.a
    librdkafka++.a librdkafka.a libtrmem.a libqos_client.a libasn1c++.a
    libthriftnb.a libthrift.a libevent.a libsqlite3.a
    libssl.a libcrypto.a libmysqlclient.a
    libfaceapi.a libcmlb.a libprotobuf.a
)

add_subdirectory(stl_cb)
add_subdirectory(mooon_cb)
add_subdirectory(json_cb)
add_subdirectory(metaprogramming_cb)
add_subdirectory(opt_cb)

option(BUILD_TEST "Whether build the tests" OFF)
if (${BUILD_TEST})
    message(STATUS "Building tests")
    enable_testing()
    add_subdirectory(test)
endif ()

