set(SOURCES
    triangle.cpp
)

add_executable(triangle ${SOURCES})

find_package(PNG)

target_link_libraries(triangle ${CODE_NAME} ${PNG_LIBRARIES} ${GEPARD_DEP_LIBS})
