cmake_minimum_required(VERSION 3.1)
project(ktcpp)

set(CMAKE_VERBOSE_MAKEFILE ON)

# pugixml
set(PUGIXML_PATH thirdparty/pugixml)
set(PUGIXML_SOURCES ${PUGIXML_PATH}/src/pugixml.cpp ${PUGIXML_PATH}/src/pugixml.hpp)

# lib
add_library(ktcpp
    src/ktcpp.cpp
    src/ktcpp.h
    ${PUGIXML_SOURCES}
)

target_compile_features(ktcpp PRIVATE cxx_std_11)

target_include_directories(ktcpp
    PUBLIC
        ${PROJECT_SOURCE_DIR}/src
        ${CMAKE_BINARY_DIR}
        ${PUGIXML_PATH}/src
)

# c++ test
add_executable(ktcpp_test test_cpp/main.cpp)
target_compile_features(ktcpp_test PRIVATE cxx_std_11)
target_link_libraries(ktcpp_test PRIVATE ktcpp)

# kotlin test
add_custom_command(TARGET ktcpp
    POST_BUILD
    COMMAND cinterop -def ${PROJECT_SOURCE_DIR}/ktcpp.def -compiler-options -I${PROJECT_SOURCE_DIR} -libraryPath ${CMAKE_BINARY_DIR} -staticLibrary libktcpp.a -o ktcpp
    COMMAND klib install ktcpp
    COMMAND kotlinc-native ${PROJECT_SOURCE_DIR}/test_kotlin/main.kt -l ktcpp -o ktcpp_test_kotlin.kexe
)
