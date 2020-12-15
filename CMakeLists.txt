cmake_minimum_required(VERSION 3.17)
project("Simple JSON" VERSION 1.0.0)
set(CMAKE_CXX_STANDARD 17)
add_executable(
        simple_json
        main.cpp
        src/types/stream_exceptions.cpp
        src/types/array_type.cpp
        src/types/bad_conversion.cpp
        src/types/invalid_index.cpp
        src/types/json.cpp
        src/types/json_key.cpp
        src/types/json_object.cpp
        src/types/indent.cpp
        src/serializer.cpp
        src/deserializer.cpp
        src/types/iterator_exceptions.cpp
        src/types/base_iterator.cpp)
target_include_directories(simple_json PUBLIC include/external)
target_include_directories(simple_json PRIVATE include/internal)