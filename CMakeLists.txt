cmake_minimum_required(VERSION 3.1)
project(aws-c-compression C)

if (DEFINED CMAKE_PREFIX_PATH)
    file(TO_CMAKE_PATH ${CMAKE_PREFIX_PATH} CMAKE_PREFIX_PATH)
endif()

if (DEFINED CMAKE_INSTALL_PREFIX)
    file(TO_CMAKE_PATH ${CMAKE_INSTALL_PREFIX} CMAKE_INSTALL_PREFIX)
endif()

if (UNIX AND NOT APPLE)
    include(GNUInstallDirs)
elseif(NOT DEFINED CMAKE_INSTALL_LIBDIR)
    set(CMAKE_INSTALL_LIBDIR "lib")
endif()

# This is required in order to append /lib/cmake to each element in CMAKE_PREFIX_PATH
set(AWS_MODULE_DIR "/${CMAKE_INSTALL_LIBDIR}/cmake")
string(REPLACE ";" "${AWS_MODULE_DIR};" AWS_MODULE_PATH "${CMAKE_PREFIX_PATH}${AWS_MODULE_DIR}")
# Append that generated list to the module search path
list(APPEND CMAKE_MODULE_PATH ${AWS_MODULE_PATH})

include(AwsCFlags)
include(AwsSharedLibSetup)
include(AwsSanitizers)
include(CheckCCompilerFlag)

file(GLOB AWS_COMPRESSION_HEADERS
        "include/aws/compression/*.h"
        )

file(GLOB AWS_COMPRESSION_PRIV_HEADERS
        "include/aws/compression/private/*.h"
        )

file(GLOB AWS_COMPRESSION_TESTING_HEADERS
        "include/aws/testing/compression/*.h"
        "include/aws/testing/compression/*.inl"
        )

file(GLOB AWS_COMPRESSION_SRC
        "source/*.c"
        )

file(GLOB COMPRESSION_HEADERS
        ${AWS_COMPRESSION_HEADERS}
        ${AWS_COMPRESSION_PRIV_HEADERS}
        ${AWS_COMPRESSION_TESTING_HEADERS}
        )

file(GLOB COMPRESSION_SRC
        ${AWS_COMPRESSION_SRC}
        )

add_library(${CMAKE_PROJECT_NAME} ${LIBTYPE} ${COMPRESSION_HEADERS} ${COMPRESSION_SRC})
aws_set_common_properties(${CMAKE_PROJECT_NAME})
aws_prepare_symbol_visibility_args(${CMAKE_PROJECT_NAME} "AWS_COMPRESSION")

aws_add_sanitizers(${CMAKE_PROJECT_NAME})

# We are not ABI stable yet
set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES VERSION 1.0.0)
set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES SOVERSION 0unstable)

target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>)

find_package(aws-c-common REQUIRED)
target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC AWS::aws-c-common)

aws_prepare_shared_lib_exports(${CMAKE_PROJECT_NAME})

install(FILES ${AWS_COMPRESSION_HEADERS} DESTINATION "include/aws/compression")
install(FILES ${AWS_COMPRESSION_TESTING_HEADERS} DESTINATION "include/aws/testing/compression")

install(EXPORT "${CMAKE_PROJECT_NAME}-targets"
        DESTINATION "${LIBRARY_DIRECTORY}/${CMAKE_PROJECT_NAME}/cmake/"
        NAMESPACE AWS::
        COMPONENT Development)

configure_file("cmake/${CMAKE_PROJECT_NAME}-config.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}-config.cmake"
        @ONLY)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}-config.cmake"
        DESTINATION "${LIBRARY_DIRECTORY}/${CMAKE_PROJECT_NAME}/cmake/"
        COMPONENT Development)

add_subdirectory(source/huffman_generator)

include(CTest)
if (BUILD_TESTING)
    add_subdirectory(tests)
endif()
