project(container_cb)
message(STATUS "sub project " ${PROJECT_NAME})

set(LinkedList
    List/linked_list.hpp
    )

set(SeqList
    List/seq_list.hpp
    )

add_executable(TestSeqList
    List/test_seq_list.cpp
    )