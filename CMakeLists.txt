cmake_minimum_required(VERSION 3.16)
project(simple-json VERSION 0.2.1)
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
set(EXTERNAL_INCLUDE_DIR "")

add_library(
        simple-json
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
        src/types/exceptions/invalid_operator.cpp
        src/types/exceptions/wrong_type.cpp
        src/json_utils.cpp
        src/types/json_pointer.cpp
        src/types/json_patch.cpp
        src/types/exceptions/failed_test.cpp
        src/types/exceptions/invalid_patch_operation.cpp
        src/types/exceptions/invalid_merge.cpp
        src/types/exceptions/base_exceptions.cpp)
target_include_directories(
        simple-json
        INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/external>$<INSTALL_INTERFACE:include/${PROJECT_NAME}/external>
)
target_include_directories(simple-json PRIVATE include/internal)

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
        VERSION ${CMAKE_PROJECT_VERSION}
        COMPATIBILITY AnyNewerVersion
)

# Installing
if (INSTALL_LIB)
    message(STATUS "Compiling Simple JSON as main project")
    install(TARGETS simple-json DESTINATION ${LIB_DIR} EXPORT ${TARGETS_EXPORT_NAME})
    install(FILES DESTINATION ${INCLUDE_DIR})
    install(DIRECTORY include/external include/internal DESTINATION ${INCLUDE_DIR})
    install(
            EXPORT ${TARGETS_EXPORT_NAME} FILE ${TARGETS_EXPORT_NAME}.cmake DESTINATION ${CONFIG_INSTALL_DIR}
    )
    install(FILES ${CONFIG_FILE} ${VERSION_CONFIG_FILE} DESTINATION ${CONFIG_INSTALL_DIR})
    include(InstallRequiredSystemLibraries)
    set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
    set(CPACK_PACKAGE_VENDOR "Sholex Team")
    set(CPACK_DEBIAN_PACKAGE_MAINTAINER ${CPACK_PACKAGE_VENDOR})
    set(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/DESCRIPTION.txt")
    set(
            CPACK_PACKAGE_DESCRIPTION_SUMMARY
            "A simple JSON library developed for modern CPP using standard library (STD) as the base."
    )
    set(CPACK_PACKAGE_FILE_NAME "${CMAKE_PROJECT_NAME}-${CMAKE_PROJECT_VERSION}")
    include(CPack)
else ()
    message(STATUS "Using Simple JSON as an Embedded project")
endif ()
