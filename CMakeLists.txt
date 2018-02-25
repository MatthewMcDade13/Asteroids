cmake_minimum_required(VERSION 2.8)
project(Asteroids)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CmakeModules" ${CMAKE_MODULE_PATH})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

find_package(SFML 2 COMPONENTS system audio window graphics REQUIRED)
find_package(PureEngine REQUIRED)
include_directories(${SFML_INCLUDE_DIR})
add_subdirectory(Asteroids)
