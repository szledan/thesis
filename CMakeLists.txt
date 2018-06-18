cmake_minimum_required(VERSION 2.8.10)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

set(CODE_NAME gepard)
set(IMG_DIR ${PROJECT_SOURCE_DIR}/paper/src/img)

add_subdirectory(code)
add_subdirectory(paper)
