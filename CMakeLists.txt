cmake_minimum_required(VERSION 2.8)

project(CirclePlot)
add_subdirectory(GeographicLib)
add_subdirectory(libzip)
add_subdirectory(pcre)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ggdb -std=c++11")
message (STATUS ${ZLIB_BUILD_DIR})
include_directories(${GeographicLib_SOURCE_DIR}/include ${ZLIB_INCLUDE_DIR} ${libzip_BINARY_DIR})
include_directories(${PCRE_SOURCE_DIR})

FILE(GLOB sources ${CMAKE_SOURCE_DIR}/*.cpp)
add_executable(circleplot ${sources})
target_link_libraries(circleplot GeographicLib zip pcre pcrecpp)
