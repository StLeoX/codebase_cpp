project(TestDemo)

add_executable(${PROJECT_NAME}
    main.cpp)

target_link_libraries(${PROJECT_NAME} gtest)

# usage: add_test(NAME <name> COMMAND <command> [<arg>...]
#        [CONFIGURATIONS <config>...]
#        [WORKING_DIRECTORY <dir>]
#        [COMMAND_EXPAND_LISTS])
# ref: https://blog.csdn.net/zcteo/article/details/117527823
add_test(NAME ${PROJECT_NAME}
    COMMAND ${PROJECT_NAME})