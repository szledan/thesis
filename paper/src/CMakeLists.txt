
add_custom_command(
    OUTPUT ${IMG_DIR}/triangle.png
    COMMAND mkdir -p ${IMG_DIR}
    COMMAND ${PROJECT_BINARY_DIR}/paper/examples/triangle/triangle ${IMG_DIR}/triangle.png
)

add_custom_command(
    OUTPUT ${IMG_DIR}/erdely.png
    COMMAND mkdir ARGS -p ${IMG_DIR}
    COMMAND ${PROJECT_BINARY_DIR}/paper/examples/erdely/erdely ARGS ${IMG_DIR}/erdely.png
)

set(LATEX_DEFAULT_BUILD safepdf)
set(PS2PDF_CONVERTER ps2pdf)
include(UseLATEX)
add_latex_document (
    szakdolgozat.tex
    INPUTS kotestabla.tex bib/cites.bib
    IMAGE_DIRS img
    BIBFILES bib/cites.bib bib/huplain.bst
    TARGET_NAME thesispaper
    DEPENDS triangle erdely
)

#add_custom_command(
#    TARGET thesispaper PRE_BUILD
#    COMMAND mkdir ARGS -p ${IMG_DIR}/
#    COMMAND inkscape ARGS --export-margin=3mm ${PROJECT_SOURCE_DIR}/paper/src/svg/dataflow.svg --export-eps=${IMG_DIR}/dataflow_eps.eps
#    DEPENDS ${PROJECT_SOURCE_DIR}/paper/src/svg/dataflow.svg
#)

file(GLOB EPS_FILES "${PROJECT_SOURCE_DIR}/paper/src/svg/*.svg")
foreach(file ${EPS_FILES})
    get_filename_component(SVG_FILENAME ${file} NAME_WE)
    set(EPS_FILE ${IMG_DIR}/${SVG_FILENAME}_eps.eps)
    add_custom_command(
        TARGET thesispaper PRE_BUILD
        COMMAND mkdir ARGS -p ${IMG_DIR}
        COMMAND inkscape ARGS --export-margin=3mm ${file} --export-eps=${EPS_FILE}
        DEPENDS ${file}
    )
endforeach()
