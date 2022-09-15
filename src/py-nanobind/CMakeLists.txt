cmake_minimum_required(VERSION 3.16)
project(py-nanobind)

set(CMAKE_SHARED_LIBRARY_PREFIX "")

set(lib_NAME pkg_nanobind)
add_library(${lib_NAME} SHARED
    py-nanobind.cpp
    pymandelbrot.cpp
    pycolor.cpp
    pyvec2.cpp
    pygameoflife.cpp
)
target_include_directories(${lib_NAME} PRIVATE 
    ${CMAKE_SOURCE_DIR}/src/
    ${CMAKE_SOURCE_DIR}/extern/nanobind/include
    ${PYTHON_INCLUDE_DIRS}
)
target_link_libraries(${lib_NAME} PRIVATE cpp-mandelbrot-lib ${PYTHON_LIBRARIES})

set_target_properties(${lib_NAME} PROPERTIES CXX_STANDARD 17)
set_target_properties(${lib_NAME} PROPERTIES POSITION_INDEPENDENT_CODE ON)
set_target_properties(${lib_NAME} PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/${DIR_PY_MODULES})


nanobuild_build_library(nanobind STATIC)
target_include_directories(nanobind PRIVATE ${PYTHON_INCLUDE_DIRS})
target_link_libraries(${lib_NAME} PRIVATE nanobind)

if (NOT MSVC)
    # snprintf(...) in nanobind/src/tensor.cpp
    target_compile_options(nanobind PRIVATE -Wno-format-truncation)
endif()