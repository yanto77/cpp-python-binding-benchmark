cmake_minimum_required(VERSION 3.16)
project(py-manual)

set(CMAKE_SHARED_LIBRARY_PREFIX "")

set(lib_NAME pkg_manual)
add_library(${lib_NAME} SHARED 
    manual-wrapper-lib.cpp
    pymandelbrot.cpp
    pymandelbrot.h
    pycolor.cpp
    pycolor.h
    pyvec2.cpp
    pyvec2.h
    pygameoflife.cpp
    pygameoflife.h
)
target_include_directories(${lib_NAME} PRIVATE 
    ${CMAKE_SOURCE_DIR}/src/
    ${PYTHON_INCLUDE_DIRS}
)
target_link_libraries(${lib_NAME} PRIVATE cpp-mandelbrot-lib ${PYTHON_LIBRARIES})

set_target_properties(${lib_NAME} PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/${DIR_PY_MODULES})
