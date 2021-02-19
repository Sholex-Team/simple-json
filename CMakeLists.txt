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
target_include_directories(
        simple_json INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>$<INSTALL_INTERFACE:include>
)
target_include_directories(simple_json PRIVATE include/internal)
install(TARGETS simple_json DESTINATION lib/${PROJECT_NAME} EXPORT simple_jsonTargets)
install(FILES include/external/simple_json.h DESTINATION include/${PROJECT_NAME})
install(DIRECTORY include/internal/ DESTINATION include/${PROJECT_NAME})
install(EXPORT simple_jsonTargets FILE simple_jsonTargets.cmake DESTINATION lib/cmake/${PROJECT_NAME})
include(CMakePackageConfigHelpers)
# generate the config file that is includes the exports
configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake/Config.cmake.in
        "${CMAKE_CURRENT_BINARY_DIR}/simple_jsonConfig.cmake"
        INSTALL_DESTINATION "lib/cmake/simple_json"
        NO_SET_AND_CHECK_MACRO
        NO_CHECK_REQUIRED_COMPONENTS_MACRO
        )
# generate the version file for the config file
write_basic_package_version_file(
        "${CMAKE_CURRENT_BINARY_DIR}/simple_jsonConfigVersion.cmake"
        VERSION "1.0.0"
        COMPATIBILITY AnyNewerVersion
)

# install the configuration file
install(FILES
        ${CMAKE_CURRENT_BINARY_DIR}/simple_jsonConfig.cmake ${CMAKE_CURRENT_BINARY_DIR}/simple_jsonConfigVersion.cmake
        DESTINATION lib/cmake/simple_json
        )