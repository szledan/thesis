set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/code/${CODE_NAME}/cmake ${PROJECT_SOURCE_DIR}/code/${CODE_NAME}/cmake/modules)

include(OptionList)
include(Dependencies)

add_subdirectory(triangle)
add_subdirectory(erdely)
