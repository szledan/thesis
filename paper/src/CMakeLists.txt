set(LATEX_DEFAULT_BUILD safepdf)
set(PS2PDF_CONVERTER ps2pdf)
include(UseLATEX)

add_custom_command(OUTPUT ${PROJECT_BINARY_DIR}/img/triangle.png
                   COMMAND mkdir ARGS -p ${PROJECT_BINARY_DIR}/img
                   COMMAND ${PROJECT_BINARY_DIR}/paper/examples/bin/triangle ARGS ${PROJECT_BINARY_DIR}/img/triangle.png
                  )

add_latex_document (
    szakdolgozat.tex
    INPUTS kotestabla.tex bib/cites.bib
    IMAGE_DIRS img
    BIBFILES bib/cites.bib bib/huplain.bst
    TARGET_NAME thesispaper
    DEPENDS ${PROJECT_BINARY_DIR}/img/triangle.png
)
