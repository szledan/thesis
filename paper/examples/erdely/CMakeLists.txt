set(SOURCES
    erdely.cpp
)

add_executable(erdely ${SOURCES})

find_package(PNG)

target_link_libraries(erdely ${CODE_NAME} ${PNG_LIBRARIES} ${GEPARD_DEP_LIBS})

add_custom_command(
    TARGET erdely POST_BUILD
    COMMAND mkdir ARGS -p ${IMG_DIR}
    COMMAND ${PROJECT_BINARY_DIR}/paper/examples/erdely/erdely ARGS ${IMG_DIR}/erdely.png
)
