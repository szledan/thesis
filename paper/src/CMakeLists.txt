set(LATEX_DEFAULT_BUILD safepdf)
set(PS2PDF_CONVERTER ps2pdf)
include(UseLATEX)

add_latex_document (
    szakdolgozat.tex
    INPUTS kotestabla.tex bib/cites.bib
    IMAGE_DIRS img img/built
    BIBFILES bib/cites.bib bib/huplain.bst
    TARGET_NAME thesispaper
    DEPENDS ${THESIS_DEPENDENCIES}
)

