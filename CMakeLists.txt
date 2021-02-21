cmake_minimum_required(VERSION 3.17)
project(simple_json VERSION 1.0.0)
set(CMAKE_CXX_STANDARD 17)

set(MAIN_PROJECT OFF)
if (CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    set(MAIN_PROJECT ON)
endif ()

# Includes
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

# Options
option(INSTALL_LIB "Install CMake targets during install step." ${MAIN_PROJECT})

# Variables
set(CONFIG_INSTALL_DIR "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}")
set(TARGETS_EXPORT_NAME "${PROJECT_NAME}Targets")
set(CONFIG_TEMPLATE "cmake/Config.cmake.in")
set(CONFIG_FILE "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake")
set(VERSION_CONFIG_FILE "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake")
set(LIB_DIR "${CMAKE_INSTALL_LIBDIR}/${PROJECT_NAME}")
set(INCLUDE_DIR "${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}")

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

# Generate the config file that is includes the exports
configure_package_config_file(
        ${CONFIG_TEMPLATE}
        ${CONFIG_FILE}
        INSTALL_DESTINATION ${CONFIG_INSTALL_DIR}
        NO_SET_AND_CHECK_MACRO
        NO_CHECK_REQUIRED_COMPONENTS_MACRO
)

# Generate the version file for the config file
write_basic_package_version_file(
        ${VERSION_CONFIG_FILE}
        VERSION "1.0.0"
        COMPATIBILITY AnyNewerVersion
)

# Installing
if (INSTALL_LIB)
    message(STATUS "Using Simple JSON as main project")
    if (CMAKE_COMPILER_IS_GNUCC)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -w")
    endif ()
    if (MSVC)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /w")
    endif ()
    install(TARGETS simple_json DESTINATION ${LIB_DIR} EXPORT ${TARGETS_EXPORT_NAME})
    install(FILES include/external/simple_json.h DESTINATION ${INCLUDE_DIR})
    install(DIRECTORY include/internal/ DESTINATION ${INCLUDE_DIR})
    install(
            EXPORT ${TARGETS_EXPORT_NAME} FILE ${TARGETS_EXPORT_NAME}.cmake DESTINATION ${CONFIG_INSTALL_DIR}
    )
    install(FILES ${CONFIG_FILE} ${VERSION_CONFIG_FILE} DESTINATION ${CONFIG_INSTALL_DIR})
else ()
    message(WARNING "Using Simple JSON as subproject")
endif ()
