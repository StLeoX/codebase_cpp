link_libraries(pthread)

add_executable(future
    future_demo01.cpp)

add_executable(thread
    thread_demo01.cpp)

add_executable(lock
    lock_demo01.cpp)

add_library(rwlock
    rwlock_impl01.cpp)