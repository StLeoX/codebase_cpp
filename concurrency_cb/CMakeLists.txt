add_executable(future
    future_demo01.cpp)
target_link_libraries(future
    pthread)


add_executable(thread
    thread_demo01.cpp)
target_link_libraries(thread
    pthread)