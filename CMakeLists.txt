cmake_minimum_required(VERSION 3.3)
project(standalone)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${standalone_SOURCE_DIR}/cmake")

add_subdirectory(clone-finder)