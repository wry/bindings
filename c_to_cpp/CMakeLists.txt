cmake_minimum_required(VERSION 3.1)
project(liblarc)

set(CMAKE_VERBOSE_MAKEFILE ON)

add_subdirectory(${PROJECT_SOURCE_DIR}/../liblar_cpp/ liblar)

add_library(larc
    src/larc.cpp
    src/larc.h
)
target_compile_features(lar PRIVATE cxx_std_11)

target_include_directories(larc
    PUBLIC
        ${PROJECT_SOURCE_DIR}/src
        ${CMAKE_BINARY_DIR}
)

target_link_libraries(larc lar)

# tests
add_executable(larc_test tests/main.c)
target_compile_features(lar PRIVATE c_std_11)
target_link_libraries(larc_test PRIVATE larc)
