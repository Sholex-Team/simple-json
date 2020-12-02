add_library(types src/BaseException.cpp src/BaseType.cpp)
target_include_directories(types INTERFACE include/external)
target_include_directories(types PRIVATE include/internal)