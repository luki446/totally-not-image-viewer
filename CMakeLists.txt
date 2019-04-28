cmake_minimum_required(VERSION 3.9)

project(TotallyNotImageViewer C)

if( CMAKE_BINARY_DIR STREQUAL CMAKE_SOURCE_DIR )
    message( FATAL_ERROR "Select other build directory for example build/" )
endif()

find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2 REQUIRED sdl2)

set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin )

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

file(GLOB SRC_FILES
    src/*.c)
file(GLOB TEST_FILE
    test.c)
include_directories(
    src/)

add_executable(tniv ${SRC_FILES})

target_link_libraries(tniv ${SDL2_LIBRARIES})
target_include_directories(tniv PUBLIC ${SDL2_INCLUDE_DIRS})
target_compile_options(tniv PUBLIC ${SDL2_CFLAGS_OTHER})