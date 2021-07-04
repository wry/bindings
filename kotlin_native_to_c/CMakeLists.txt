cmake_minimum_required(VERSION 3.1)
project(ktlar)

set(CMAKE_VERBOSE_MAKEFILE ON)

add_subdirectory(${PROJECT_SOURCE_DIR}/../c_to_cpp/ larc)

add_library(fakey fakey.c)
target_link_libraries(fakey larc)

add_custom_command(TARGET fakey POST_BUILD
    COMMAND cinterop -pkg lar -header ${PROJECT_SOURCE_DIR}/../c_to_cpp/src/larc.h -compiler-options -I${PROJECT_SOURCE_DIR}/../c_to_cpp/src/ -libraryPath ${CMAKE_BINARY_DIR}/larc -staticLibrary liblarc.a -libraryPath ${CMAKE_BINARY_DIR}/larc/liblar -staticLibrary liblar.a -o lar
    COMMAND klib install lar
    COMMAND kotlinc-native ${PROJECT_SOURCE_DIR}/src/main.kt -l lar -o ktlar_test.kexe
    DEPENDS ${PROJECT_SOURCE_DIR}/src/main.kt
)
