cmake_minimum_required(VERSION 3.16)
project(benchmark-python-glue-code)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(BENCH_MANDELBROT_SIZE_X "1000")
set(BENCH_MANDELBROT_SIZE_Y "1000")
set(BENCH_MANDELBROT_MAX_ITER "100")

set(BENCH_GAMEOFLIFE_ROWS "200")
set(BENCH_GAMEOFLIFE_COLS "200")
set(BENCH_GAMEOFLIFE_MAX_ITER "100")
set(BENCH_GAMEOFLIFE_CELLS_START "13192")
set(BENCH_GAMEOFLIFE_CELLS_END "1946")

set(DIR_PY_MODULES "lib_python")

find_package(PythonLibs REQUIRED)

add_subdirectory(extern/nanobind)

add_subdirectory(src/cpp-lib)
add_subdirectory(src/cpp-execs)
add_subdirectory(src/py-scripts)
add_subdirectory(src/py-manual)
add_subdirectory(src/py-pybind11)
add_subdirectory(src/py-nanobind)
add_subdirectory(src/py-cython)
add_subdirectory(src/py-swig)
add_subdirectory(src/py-cffi)
add_subdirectory(src/py-cppyy)
