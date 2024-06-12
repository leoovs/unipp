cmake_minimum_required(VERSION 3.16)

project(unipp)

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

add_subdirectory("unipp")
add_subdirectory("example")

