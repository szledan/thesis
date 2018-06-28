add_subdirectory(examples)

list(APPEND THESIS_DEPENDENCIES "")

set(BUILT_IMG_DIR ${PROJECT_SOURCE_DIR}/paper/src/img/built)
file(MAKE_DIRECTORY ${BUILT_IMG_DIR})

# Run example/triangle to generate output
add_custom_command(
    OUTPUT ${BUILT_IMG_DIR}/triangle.png
    COMMAND ${PROJECT_BINARY_DIR}/paper/examples/triangle/triangle ${BUILT_IMG_DIR}/triangle.png
    DEPENDS triangle
)
add_custom_target(triangle.png ALL DEPENDS ${BUILT_IMG_DIR}/triangle.png)
list(APPEND THESIS_DEPENDENCIES triangle.png)

# Run example/erdely to generate output
add_custom_command(
    OUTPUT ${BUILT_IMG_DIR}/erdely.png
    COMMAND ${PROJECT_BINARY_DIR}/paper/examples/erdely/erdely ARGS ${BUILT_IMG_DIR}/erdely.png
    DEPENDS erdely
)
add_custom_target(erdely.png ALL DEPENDS ${BUILT_IMG_DIR}/erdely.png)
list(APPEND THESIS_DEPENDENCIES erdely.png)

# Convert SVG files to EPS ones
file(GLOB EPS_FILES "${PROJECT_SOURCE_DIR}/paper/src/svg/*.svg")
foreach(file ${EPS_FILES})
    get_filename_component(SVG_FILENAME ${file} NAME_WE)
    set(EPS_FILE ${BUILT_IMG_DIR}/${SVG_FILENAME}_eps.eps)
    add_custom_command(
        OUTPUT ${EPS_FILE}
        COMMAND inkscape ARGS --export-margin=3mm ${file} --export-eps=${EPS_FILE}
        DEPENDS ${file}
    )
    add_custom_target(${SVG_FILENAME}_eps ALL DEPENDS ${EPS_FILE})
    list(APPEND THESIS_DEPENDENCIES ${SVG_FILENAME}_eps)
endforeach()

add_subdirectory(src)

set(LATEX_DEFAULT_BUILD safepdf)
set(PS2PDF_CONVERTER ps2pdf)
include(UseLATEX)

add_latex_document (
    plan.tex
    INPUTS src/bib/huplain.bst
    TARGET_NAME plan.tex
)
