project(types VERSION 1.0.0)

# library
add_library(
        types
        src/bad_conversion.cpp
        src/json_item.cpp
        src/enum_types.cpp
        src/json_type.cpp
        include/internal/base_exception.h)

# set variables
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

# include directories
target_include_directories(types INTERFACE ${INCLUDE_DIR}/external)
target_include_directories(types PRIVATE ${INCLUDE_DIR}/internal)