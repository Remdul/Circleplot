project(CirclePlot)
add_subdirectory(geographicLib)
add_subdirectory(libzip)

include_directories(${GeographicLib_SOURCE_DIR}/include)

FILE(GLOB sources ${CMAKE_SOURCE_DIR}/*.cpp)
add_executable(circleplot ${sources})
target_link_libraries(circleplot geographicLib libzip)

