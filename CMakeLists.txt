cmake_minimum_required(VERSION 2.8)

project(CirclePlot)
add_subdirectory(GeographicLib)
add_subdirectory(libzip)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(BOOST_lIBRARYDIR /usr/local/boost_1_55_0/stage/lib/)
set(Boost_INCLUDE_DIR /usr/local/boost_1_55_0)
FIND_PACKAGE(Boost COMPONENTS system filesystem regex REQUIRED)
message (STATUS ${ZLIB_BUILD_DIR})
include_directories(${GeographicLib_SOURCE_DIR}/include ${Boost_INCLUDE_DIR} ${ZLIB_INCLUDE_DIR} ${libzip_BINARY_DIR})
link_directories(${Boost_LIBRARY_DIR})

FILE(GLOB sources ${CMAKE_SOURCE_DIR}/*.cpp)
add_executable(circleplot ${sources})
target_link_libraries(circleplot GeographicLib zip ${Boost_LIBRARIES})

