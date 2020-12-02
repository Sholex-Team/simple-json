project(types VERSION 1.0.0)

# library
add_library(types src/BaseException.cpp src/BaseType.cpp)

# set variables
set(INCLUDE_DER ${CMAKE_CURRENT_SOURCE_DIR}/include)

# include directories
target_include_directories(types PRIVATE ${INCLUDE_DER}/internal)
target_include_directories(types INTERFACE ${INCLUDE_DER}/external)