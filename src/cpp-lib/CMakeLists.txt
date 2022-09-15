cmake_minimum_required (VERSION 3.16)
project (cpp-mandelbrot-lib LANGUAGES CXX)

set(lib_NAME cpp-mandelbrot-lib)
add_library(${lib_NAME} SHARED 
    mandelbrot.cpp mandelbrot.h # c++ interface
    cmandelbrot.cpp cmandelbrot.h # c interface

    gameoflife.cpp gameoflife.h # c++ interface
    cgameoflife.cpp cgameoflife.h # c interface
)
set_target_properties(${lib_NAME} PROPERTIES POSITION_INDEPENDENT_CODE ON)

add_custom_command(TARGET ${lib_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${PROJECT_SOURCE_DIR}/mandelbrot.h"
        "${CMAKE_BINARY_DIR}/bin/lib/include/mandelbrot.h"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${PROJECT_SOURCE_DIR}/cmandelbrot.h"
        "${CMAKE_BINARY_DIR}/bin/lib/include/cmandelbrot.h"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${PROJECT_SOURCE_DIR}/gameoflife.h"
        "${CMAKE_BINARY_DIR}/bin/lib/include/gameoflife.h"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${PROJECT_SOURCE_DIR}/cgameoflife.h"
        "${CMAKE_BINARY_DIR}/bin/lib/include/cgameoflife.h"
    COMMENT "Copying headers to build dir"
)