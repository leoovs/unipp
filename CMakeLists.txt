cmake_minimum_required(VERSION 3.16)

project(unipp)

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

add_subdirectory("example")
add_subdirectory("testbed")
add_subdirectory("unipp")

