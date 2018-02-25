cmake_minimum_required(VERSION 2.8)
project(Asteroids)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CmakeModules" ${CMAKE_MODULE_PATH})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

configure_file("${CMAKE_BINARY_DIR}/Asteroids/ARCADE_N.TTF" "${CMAKE_BINARY_DIR}/bin/" COPYONLY)
configure_file("${CMAKE_BINARY_DIR}/Asteroids/explode.wav" "${CMAKE_BINARY_DIR}/bin/" COPYONLY)
configure_file("${CMAKE_BINARY_DIR}/Asteroids/lazer_shoot.wav" "${CMAKE_BINARY_DIR}/bin/" COPYONLY)
configure_file("${CMAKE_BINARY_DIR}/Asteroids/Space_Chase_Music.wav" "${CMAKE_BINARY_DIR}/bin/" COPYONLY)

find_package(SFML 2 COMPONENTS system audio window graphics REQUIRED)
find_package(PureEngine REQUIRED)
include_directories(${SFML_INCLUDE_DIR})
add_subdirectory(Asteroids)
