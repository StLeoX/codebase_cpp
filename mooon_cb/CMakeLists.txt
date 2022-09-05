cmake_minimum_required(VERSION 2.8)
project(mooon_cb)

add_executable(mooon_cb
    test_mooon.cpp)

# 系统库
set(BASE_HOME /usr/local/)
# include(${BASE_HOME}/CMake.common) # common cmake scripts
include_directories(${BASE_HOME}/include) # headers
link_directories(${BASE_HOME}/lib) # static libraries, e.x. libmooon.a in it


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
