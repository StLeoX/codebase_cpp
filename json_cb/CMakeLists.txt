include_directories(/usr/local/rapidjson/include)

add_executable(test_json test_json.cpp)
target_link_libraries(test_json
        ${THIRDPART_LIB}
        )