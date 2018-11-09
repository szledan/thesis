add_subdirectory(examples)

list(APPEND THESIS_DEPENDENCIES "")

set(BUILT_IMG_DIR ${PROJECT_SOURCE_DIR}/paper/src/img/built)
set(SRC_ROOT_DIR ${PROJECT_SOURCE_DIR}/paper/src/)
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

# Run code/gepard/apps/svggepard to generate tiger.png output
add_custom_command(
    OUTPUT ${BUILT_IMG_DIR}/tiger.png
    COMMAND ${PROJECT_BINARY_DIR}/code/${CODE_NAME}/bin/svggepard ARGS -p ${BUILT_IMG_DIR}/tiger.png ${PROJECT_SOURCE_DIR}/code/${CODE_NAME}/apps/svggepard/tiger.svg
    DEPENDS svggepard
)
add_custom_target(tiger.png ALL DEPENDS ${BUILT_IMG_DIR}/tiger.png)
list(APPEND THESIS_DEPENDENCIES tiger.png)

# Convert SVG files to EPS ones
file(GLOB EPS_FILES "${PROJECT_SOURCE_DIR}/paper/src/svg/*.svg")
foreach(file ${EPS_FILES})
    get_filename_component(SVG_FILENAME ${file} NAME_WE)
    set(EPS_FILE ${BUILT_IMG_DIR}/${SVG_FILENAME}_eps.eps)
    add_custom_command(
        OUTPUT ${EPS_FILE}
        COMMAND inkscape ARGS --export-area-drawing --export-margin=0mm ${file} --export-eps=${EPS_FILE}
        DEPENDS ${file}
    )
    add_custom_target(${SVG_FILENAME}_eps ALL DEPENDS ${EPS_FILE})
    list(APPEND THESIS_DEPENDENCIES ${SVG_FILENAME}_eps)
endforeach()

# Compare 'tiger' images and create diffover.png
add_custom_command(
    OUTPUT ${BUILT_IMG_DIR}/diffover.png
    COMMAND ${PROJECT_SOURCE_DIR}/scripts/compare-images.sh ARGS 1
    DEPENDS tiger.png ${BUILT_IMG_DIR}/tiger.png
)
add_custom_target(diffover.png ALL DEPENDS ${BUILT_IMG_DIR}/diffover.png)
list(APPEND THESIS_DEPENDENCIES diffover.png)

# Compare 'tiger' images and calculate SSIM color values
add_custom_command(
    OUTPUT ${SRC_ROOT_DIR}/res/ssim.txt
    COMMAND ${PROJECT_SOURCE_DIR}/scripts/compare-images.sh ARGS 2
    DEPENDS tiger.png ${BUILT_IMG_DIR}/tiger.png
)
add_custom_target(ssim ALL DEPENDS ${SRC_ROOT_DIR}/res/ssim.txt)
list(APPEND THESIS_DEPENDENCIES ssim)

# Compare 'tiger' images and calculate SSIM values
add_custom_command(
    OUTPUT ${SRC_ROOT_DIR}/res/ssim-psnr.txt
    COMMAND ${PROJECT_SOURCE_DIR}/scripts/compare-images.sh ARGS 3
    DEPENDS tiger.png ${BUILT_IMG_DIR}/tiger.png
)
add_custom_target(ssim-psnr ALL DEPENDS ${SRC_ROOT_DIR}/res/ssim-psnr.txt)
list(APPEND THESIS_DEPENDENCIES ssim-psnr)

add_subdirectory(src)

set(LATEX_DEFAULT_BUILD safepdf)
set(PS2PDF_CONVERTER ps2pdf)
include(UseLATEX)

add_latex_document (
    plan.tex
    INPUTS src/bib/huplain.bst
    TARGET_NAME plan.tex
)
