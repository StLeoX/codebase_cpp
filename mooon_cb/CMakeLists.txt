project(mooon_cb)
message(STATUS "sub project " ${PROJECT_NAME})
# using common cmake scripts
include(/usr/local/lib/cmake/mooon.cmake)

# 常用的第三方库
add_library(
    THIRDPART
    STATIC IMPORTED
    libgongyi_base.a
    libmooon.a
    libr3c.a libhiredis.a
    libcgicc.a libcurl.a libcares.a libidn.a
    librdkafka++.a librdkafka.a libtrmem.a libqos_client.a libasn1c++.a
    libthriftnb.a libthrift.a libevent.a libsqlite3.a
    libssl.a libcrypto.a libmysqlclient.a
    libfaceapi.a libcmlb.a libprotobuf.a
)

add_executable(mooon_cb
    test_mooon.cpp)
