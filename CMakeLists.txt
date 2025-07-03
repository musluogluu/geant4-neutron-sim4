cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project(geant4-neutron-sim4 LANGUAGES CXX)

# C++11 standardı
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Geant4 REQUIRED)
include(${Geant4_USE_FILE})

set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

file(GLOB SOURCES
    src/*.cc
    main.cc
)

add_executable(main ${SOURCES})

target_include_directories(main PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(main ${Geant4_LIBRARIES})

target_compile_options(main PRIVATE
    -Wall
    -Wextra
    -pedantic
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)