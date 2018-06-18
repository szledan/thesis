set(SOURCES
    triangle.cpp
)

add_executable(triangle ${SOURCES})

find_package(PNG)

target_link_libraries(triangle ${CODE_NAME} ${PNG_LIBRARIES} ${GEPARD_DEP_LIBS})

add_custom_command(
    TARGET triangle POST_BUILD
    COMMAND mkdir ARGS -p ${IMG_DIR}
    COMMAND ${PROJECT_BINARY_DIR}/paper/examples/triangle/triangle ARGS ${IMG_DIR}/triangle.png
)
