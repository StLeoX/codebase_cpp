cmake_minimum_required(VERSION 2.8)
project(cpp_code_base)

# 寻找公益base库
if (EXISTS /usr/local/gongyi/base/CMake.common)
    message("${Yellow}gongyi_base at /usr/local/gongyi/base ${ColourReset}")
    set(BASE_HOME /usr/local/gongyi/base)
else ()
    message("${Yellow}NOT found gongyi base (/usr/local/gongyi/base or /usr/local/gy_lib/base) ${ColourReset}")
    return ()
endif ()

# 公益base库
include(${BASE_HOME}/CMake.common)
include_directories(${BASE_HOME}/include)
link_directories(${BASE_HOME}/lib)

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
        libfaceapi.a libcmlb.a libprotobuf.a # 取昵称依赖
)

add_subdirectory(stl_cb)
add_subdirectory(mooon_cb)
add_subdirectory(json_cb)