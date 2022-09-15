cmake_minimum_required(VERSION 3.16)
project(py-pybind11)

set(CMAKE_SHARED_LIBRARY_PREFIX "")

set(lib_NAME pkg_pybind11)
add_library(${lib_NAME} SHARED 
    py-pybind11.cpp
    pymandelbrot.cpp
    pycolor.cpp
    pyvec2.cpp
    pygameoflife.cpp
)
target_include_directories(${lib_NAME} PRIVATE 
    ${CMAKE_SOURCE_DIR}/src/
    ${CMAKE_SOURCE_DIR}/extern/pybind11/include
    ${PYTHON_INCLUDE_DIRS}
    
)
target_link_libraries(${lib_NAME} PRIVATE cpp-mandelbrot-lib ${PYTHON_LIBRARIES})

set_target_properties(${lib_NAME} PROPERTIES CXX_STANDARD 17)
set_target_properties(${lib_NAME} PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/${DIR_PY_MODULES})
