add_executable(test_mooon test_mooon.cpp)

# 系统库
set(BASE_HOME /usr/local/)
# include(${BASE_HOME}/CMake.common) # common cmake scripts
include_directories(${BASE_HOME}/include) # headers
link_directories(${BASE_HOME}/lib) # static libraries, e.x. libmooon.a in it
