project(types VERSION 1.0.0)

# library
add_library(
        types
        src/json_item.cpp
        src/array_type.cpp
        src/json_type.cpp
        src/enum_types.cpp
        src/bad_conversion.cpp
        src/stream_exceptions.cpp
        src/invalid_index_exception.cpp include/internal/invalid_index_exception.h)

# set variables
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

# include directories
target_include_directories(types INTERFACE ${INCLUDE_DIR}/external)
target_include_directories(types PRIVATE ${INCLUDE_DIR}/internal)