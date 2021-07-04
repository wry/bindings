cmake_minimum_required(VERSION 3.1)
project(liblar)

set(CMAKE_VERBOSE_MAKEFILE ON)

# pugixml
set(PUGIXML_PATH thirdparty/pugixml)
set(PUGIXML_SOURCES ${PUGIXML_PATH}/src/pugixml.cpp ${PUGIXML_PATH}/src/pugixml.hpp)

add_library(lar
    src/lar.cpp
    src/lar.h
    ${PUGIXML_SOURCES}
)

target_compile_features(lar PRIVATE cxx_std_11)

target_include_directories(lar
    PUBLIC
        ${PROJECT_SOURCE_DIR}/src
        ${CMAKE_BINARY_DIR}
        ${PUGIXML_PATH}/src
)

# tests
add_executable(lar_test tests/main.cpp)
target_compile_features(lar_test PRIVATE cxx_std_11)
target_link_libraries(lar_test PRIVATE lar)
