set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/code/${CODE_NAME}/cmake ${PROJECT_SOURCE_DIR}/code/${CODE_NAME}/cmake/modules)

include(OptionList)
include(Dependencies)

set(EXTRA_FLAGS "-Wall -pedantic -std=c++11")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${EXTRA_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${EXTRA_FLAGS}")

add_dependencies(examples ${CODE_NAME})

add_subdirectory(triangle)
add_subdirectory(erdely)
