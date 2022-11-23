project(concurrency_cb)
message(STATUS "sub project " ${PROJECT_NAME})

link_libraries(pthread)

add_executable(condvar_demo
    condvar_demo01.cpp)

add_executable(future_demo
    future_demo01.cpp)

add_executable(lock_demo
    lock_demo01.cpp)

add_library(rwlock
    rwlock_impl01.cpp)

add_executable(thread_demo
    thread_demo01.cpp)
