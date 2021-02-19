cmake_minimum_required(VERSION 3.17)
project(simple_json VERSION 1.0.0)
set(CMAKE_CXX_STANDARD 17)
add_library(
        simple_json
        src/types/exceptions/stream_exceptions.cpp
        src/types/array_type.cpp
        src/types/exceptions/bad_conversion.cpp
        src/types/exceptions/invalid_index.cpp
        src/types/exceptions/invalid_pointer.cpp
        src/types/json.cpp
        src/types/json_key.cpp
        src/types/json_object.cpp
        src/indent.cpp
        src/serializer.cpp
        src/deserializer.cpp
        src/types/exceptions/iterator_exceptions.cpp
        src/types/base_iterator.cpp
        src/types/exceptions/deserializer_exceptions.cpp
        src/types/exceptions/invalid_operation.cpp
        src/json_utils.cpp
        src/types/json_pointer.cpp
        src/types/json_patch.cpp
        src/types/exceptions/failed_test.cpp
        src/types/exceptions/invalid_patch_operation.cpp
        src/types/exceptions/invalid_merge.cpp
)
target_include_directories(simple_json INTERFACE include/external)
target_include_directories(simple_json PRIVATE include/internal)
install(TARGETS simple_json DESTINATION lib/${PROJECT_NAME})
install(FILES include/external/simple_json.h DESTINATION include/${PROJECT_NAME})
install(DIRECTORY include/internal/ DESTINATION include/${PROJECT_NAME})