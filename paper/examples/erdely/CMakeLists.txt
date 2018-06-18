set(SOURCES
    erdely.cpp
)

add_executable(erdely ${SOURCES})

find_package(PNG)

target_link_libraries(erdely ${CODE_NAME} ${PNG_LIBRARIES} ${GEPARD_DEP_LIBS})
