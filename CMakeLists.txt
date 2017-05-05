cmake_minimum_required (VERSION 3.8)
project(BloomFilter CXX)

find_package(Doxygen)
if(DOXYGEN_FOUND)
    add_custom_target(doxygen ALL
        ${DOXYGEN_EXECUTABLE}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT "Generating API documentation with Doxygen" VERBATIM
        SOURCES Doxyfile
    )
endif(DOXYGEN_FOUND)

add_definitions(
    -DNOMINMAX
    -DWIN32_LEAN_AND_MEAN
    -DVC_EXTRALEAN
    -D_CRT_SECURE_NO_WARNINGS
    -D_SECURE_SCL=0
    -D_SCL_SECURE_NO_WARNINGS
)

option(BUILD_SHARED_LIBS "Build libraries as DLLs" FALSE)

#set(BloomFilter_VERSION_MAJOR 0)
#set(BloomFilter_VERSION_MINOR 1)
#configure_file("${PROJECT_SOURCE_DIR}/Version.h.in" "${PROJECT_BINARY_DIR}/Version.h")

set(PUBLIC_INCLUDE_PATHS
    include
)

set(PRIVATE_INCLUDE_PATHS
    src
)

set(SOURCES
    src/BloomFilter.cpp
    include/BloomFilter/BloomFilter.h
)

add_library(BloomFilter ${SOURCES})
#target_compile_definitions(BloomFilter PRIVATE ${DEFINES})
target_include_directories(BloomFilter PRIVATE ${PRIVATE_INCLUDE_PATHS} PUBLIC ${PUBLIC_INCLUDE_PATHS})
source_group(Sources FILES ${SOURCES})
