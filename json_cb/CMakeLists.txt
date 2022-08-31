include_directories(/usr/local/rapidjson/include)

add_executable(json_cb
    test_json.cpp)
target_link_libraries(json_cb
    ${THIRDPART_LIB})